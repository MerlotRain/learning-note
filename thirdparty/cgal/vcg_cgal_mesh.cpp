

#include <FJDCoreLib/GenericIndexedCloudPersist.h>

#include <vcg/complex/complex.h>

#include <vcg/complex/algorithms/update/color.h>

#include <wrap/io_trimesh/import.h>
#include <wrap/io_trimesh/export_ply.h>
#include <wrap/io_trimesh/export_obj.h>

#include <vcg/complex/algorithms/update/topology.h>
#include <cmath>
class MyFace;
class MyVertex;
struct MyUsedTypes : public vcg::UsedTypes<	vcg::Use<MyVertex>::AsVertexType, vcg::Use<MyFace>::AsFaceType> {};
class MyVertex : public vcg::Vertex< MyUsedTypes, vcg::vertex::Coord3f, vcg::vertex::Normal3f, vcg::vertex::Color4b, vcg::vertex::BitFlags  > {};
class MyFace : public vcg::Face < MyUsedTypes, vcg::face::VertexRef, vcg::face::Normal3f, vcg::face::Color4b, vcg::face::BitFlags > {};
class MeshType : public vcg::tri::TriMesh< std::vector<MyVertex>, std::vector<MyFace> > {};


#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Point_set_3.h>
#include <CGAL/Point_set_3/IO.h>
#include <CGAL/remove_outliers.h>
#include <CGAL/grid_simplify_point_set.h>
#include <CGAL/random_simplify_point_set.h>
#include <CGAL/jet_smooth_point_set.h>
#include <CGAL/jet_estimate_normals.h>
#include <CGAL/mst_orient_normals.h>
#include <CGAL/poisson_surface_reconstruction.h>
#include <CGAL/Advancing_front_surface_reconstruction.h>
#include <CGAL/Scale_space_surface_reconstruction_3.h>
#include <CGAL/Scale_space_reconstruction_3/Jet_smoother.h>
#include <CGAL/Scale_space_reconstruction_3/Advancing_front_mesher.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>

#include <CGAL/Polygon_mesh_processing/triangulate_hole.h>
#include <CGAL/Polygon_mesh_processing/border.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
#include <CGAL/Real_timer.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3                                     Point_3;
typedef CGAL::Surface_mesh<Point_3>                           Mesh;
typedef boost::graph_traits<Mesh>::vertex_descriptor        vertex_descriptor;
typedef boost::graph_traits<Mesh>::halfedge_descriptor      halfedge_descriptor;
typedef boost::graph_traits<Mesh>::face_descriptor          face_descriptor;
namespace PMP = CGAL::Polygon_mesh_processing;
bool is_small_hole(halfedge_descriptor h, Mesh & mesh,
    double max_hole_diam, int max_num_hole_edges)
{
    int num_hole_edges = 0;
    CGAL::Bbox_3 hole_bbox;
    for (halfedge_descriptor hc : CGAL::halfedges_around_face(h, mesh))
    {
        const Point_3& p = mesh.point(target(hc, mesh));
        hole_bbox += p.bbox();
        ++num_hole_edges;
        // Exit early, to avoid unnecessary traversal of large holes
        if (num_hole_edges > max_num_hole_edges) return false;
        if (hole_bbox.xmax() - hole_bbox.xmin() > max_hole_diam) return false;
        if (hole_bbox.ymax() - hole_bbox.ymin() > max_hole_diam) return false;
        if (hole_bbox.zmax() - hole_bbox.zmin() > max_hole_diam) return false;
    }
    return true;
}

using namespace CCCoreLib;

bool CreateCgalMesh::buildSurfaceMesh(ccGenericPointCloud* cloud,
    int surfaceMeshMethodType,
    double spacing,
    std::string tempFile,
    std::string& outputErrorStr,
    bool isFillHoles)
{

    MeshType m;
    using FT = Kernel::FT;
    using Vector_3 = Kernel::Vector_3;
    using Sphere_3 = Kernel::Sphere_3;
    using Point_set = CGAL::Point_set_3<Point_3, Vector_3>;
    Point_set points;
    std::size_t pointCount = cloud->size();
    if (pointCount < 3)
    {
        outputErrorStr = "Not enough points";
        return false;
    }
    try
    {
        points.resize(pointCount);
    }
    catch (const std::bad_alloc&)
    {
        outputErrorStr = "Not enough memory";
        return false;
    };

    std::vector<Eigen::Matrix3d> vertColor(pointCount,Eigen::Matrix3d());
    cloud->placeIteratorAtBeginning();
    for (unsigned i = 0; i < pointCount; ++i)
    {
        const CCVector3* p = cloud->getPoint(i);
        points.point(i) = Point_3(p->x, p->y, p->z);
        if (cloud->hasColors())
        {
            const ccColor::Rgba p_color = cloud->getPointColor(i);
            vertColor.at(i)(0) = p_color.r;
            vertColor.at(i)(1) = p_color.g;
            vertColor.at(i)(2) = p_color.b;
        }
    }
    try
    {
        int reconstruction_choice = surfaceMeshMethodType;
        CGAL::Surface_mesh<Point_3> output_mesh;
        if (reconstruction_choice == 3 || reconstruction_choice == -1) // Poisson
        {
            ///////////////////////////////////////////////////////////////////
            //! [Normal estimation]
            CGAL::jet_estimate_normals<CGAL::Sequential_tag>
                (points, 24); // Use 24 neighbors
            // Orientation of normals, returns iterator to first unoriented point
            typename Point_set::iterator unoriented_points_begin =
                CGAL::mst_orient_normals(points, 24); // Use 24 neighbors
            points.remove(unoriented_points_begin, points.end());
            //! [Normal estimation]
            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////
            //! [Poisson reconstruction]
            CGAL::poisson_surface_reconstruction_delaunay
            (points.begin(), points.end(),
                points.point_map(), points.normal_map(),
                output_mesh, spacing);
            //! [Poisson reconstruction]
            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////
            //! [Output poisson]
            ///////////////////////////////////////////////////////////////////
        }
        if (reconstruction_choice == 0 || reconstruction_choice == -1) // Advancing front
        {
            ///////////////////////////////////////////////////////////////////
            //! [Advancing front reconstruction]
            //typedef std::array<std::size_t, 3> Facet; // Triple of indices
            std::vector<Facet> facets;
            // The function is called using directly the points raw iterators
            CGAL::advancing_front_surface_reconstruction(points.points().begin(),
                points.points().end(),
                std::back_inserter(facets));
            std::cout << facets.size()
                << " facet(s) generated by reconstruction." << std::endl;
            //! [Advancing front reconstruction]
            ///////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////
            //! [Output advancing front]
            // copy points for random access
            std::vector<Point_3> vertices;
            vertices.reserve(points.size());
            std::copy(points.points().begin(), points.points().end(), std::back_inserter(vertices));
            CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(vertices, facets, output_mesh);

            Eigen::MatrixXf vertMatrix;
            vertMatrix.resize(vertices.size(), 3);

            for (size_t i = 0; i < vertices.size(); ++i) {
                const Point_3& p = vertices[i];
                vertMatrix(i, 0) = p.x();
                vertMatrix(i, 1) = p.y();
                vertMatrix(i, 2) = p.z();
            }          
            vcg::tri::Allocator<MeshType>::AddVertices(m, vertMatrix);
            for (size_t i = 0; i < m.vert.size(); i++)
                m.vert[i].C() = vcg::Color4b(vertColor[i](0), vertColor[i](1), vertColor[i](2), 255);
            //MeshType::VertexIterator v_ret = vcg::tri::Allocator<MeshType>::AddVertices(m, vertices.size());
            /*for (size_t i = 0; i < vertices.size(); ++i)
            {
                (&*v_ret)->P()[0] = vertices[i][0];
                (&*v_ret)->P()[1] = vertices[i][1];
                (&*v_ret)->P()[2] = vertices[i][2];
                ++v_ret;
            }*/
            MeshType::FaceIterator f_ret = vcg::tri::Allocator<MeshType>::AddFaces(m, facets.size());
            for (size_t i = 0; i < facets.size(); ++i)
            {
                int v0_retidx = facets[i][0];
                int v1_retidx = facets[i][1];
                int v2_retidx = facets[i][2];
                MeshType::VertexPointer ivp[4];
                //ivp[0] = m.vert.at(v1_retidx).P();
                ivp[0] = &m.vert[v0_retidx];
                ivp[1] = &m.vert[v1_retidx];
                ivp[2] = &m.vert[v2_retidx];
                (*&f_ret)->V(0) = ivp[0];
                (*&f_ret)->V(1) = ivp[1];
                (*&f_ret)->V(2) = ivp[2];
                ++f_ret;
            }
            vcg::tri::UpdateColor<MeshType>::PerFaceFromVertex(m);
            std::vector<MeshType::FaceIterator> faces_to_delete;
            for (MeshType::FaceIterator fit = m.face.begin();fit != m.face.end();++fit)
            {
                MyFace *face = static_cast<MyFace *>(&(*fit));
                bool delete_face = false;
                for (int i = 0; i < 3; ++i)
                {
                    MeshType::VertexType *v0 = face->V(i);
                    MeshType::VertexType *v1 = face->V((i + 1) % 3);
                    MeshType::VertexType *v2 = face->V((i + 2) % 3);
                    if (!v0 || !v1 || !v2)
                    {
                        delete_face = true;
                        break;
                    }

                    vcg::Point3f edge_vector = v1->P() - v0->P();
                    float edge_length_squared = edge_vector.X() * edge_vector.X() + edge_vector.Y() * edge_vector.Y() +
                                                edge_vector.Z() * edge_vector.Z();
                    float edge_length = std::sqrt(edge_length_squared);
                    if (edge_length > 3 * spacing)
                    {
                        delete_face = true;
                        break;
                    }
                }
                if (delete_face)
                {
                    faces_to_delete.push_back(fit);
                }
            }
            for (auto it = faces_to_delete.rbegin(); it != faces_to_delete.rend(); ++it)
            {
                m.face.erase(*it);
            }
            vcg::tri::io::ExporterOBJ<MeshType>::Save(m, "vcg_mesh_test1.obj", vcg::tri::io::Mask::IOM_VERTCOLOR);
        }
        if (reconstruction_choice == 1 || reconstruction_choice == -1) // Scale space
        {
            ///////////////////////////////////////////////////////////////////
            //! [Scale space reconstruction]
            CGAL::Scale_space_surface_reconstruction_3<Kernel> reconstruct
            (points.points().begin(), points.points().end());
            // Smooth using 4 iterations of Jet Smoothing
            reconstruct.increase_scale(4, CGAL::Scale_space_reconstruction_3::Jet_smoother<Kernel>());
            // Mesh with the Advancing Front mesher with a maximum facet length of 0.5
            reconstruct.reconstruct_surface(CGAL::Scale_space_reconstruction_3::Advancing_front_mesher<Kernel>(0.5));
            //! [Scale space reconstruction]
            ///////////////////////////////////////////////////////////////////

            typedef std::array<std::size_t, 3> Facet; // Triple of indices
            std::vector<Facet> facets;
            facets.reserve(reconstruct.number_of_facets());
            std::copy(reconstruct.facets_begin(), reconstruct.facets_end(), std::back_inserter(facets));
            // copy points for random access
            std::vector<Point_3> vertices;
            vertices.reserve(points.size());
            std::copy(points.points().begin(), points.points().end(), std::back_inserter(vertices));
            CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(vertices, facets, output_mesh);
            ///////////////////////////////////////////////////////////////////
            //! [Output scale space]
           /* std::ofstream f(tempFile);
            f << "OFF" << std::endl << points.size() << " "
                << reconstruct.number_of_facets() << " 0" << std::endl;
            for (Point_set::Index idx : points)
                f << points.point(idx) << std::endl;
            for (const auto& facet : CGAL::make_range(reconstruct.facets_begin(), reconstruct.facets_end()))
                f << "3 " << facet << std::endl;
            f.close();*/
            //! [Output scale space]
            ///////////////////////////////////////////////////////////////////
        }

        if(isFillHoles)
        {
            // Both of these must be positive in order to be considered
            double max_hole_diam = -1.0;
            //double max_hole_diam = 10;
            int max_num_hole_edges = -1;
            //int max_num_hole_edges = 50;
            unsigned int nb_holes = 0;
            std::vector<halfedge_descriptor> border_cycles;
            // collect one halfedge per boundary cycle
            PMP::extract_boundary_cycles(output_mesh, std::back_inserter(border_cycles));
            for (halfedge_descriptor h : border_cycles)
            {
                if (max_hole_diam > 0 && max_num_hole_edges > 0 &&
                    !is_small_hole(h, output_mesh, max_hole_diam, max_num_hole_edges))
                    continue;
                std::vector<face_descriptor>  patch_facets;
                std::vector<vertex_descriptor> patch_vertices;
                bool success = std::get<0>(PMP::triangulate_refine_and_fair_hole(output_mesh,
                    h,
                    std::back_inserter(patch_facets),
                    std::back_inserter(patch_vertices)));
                //std::cout << "* Number of facets in constructed patch: " << patch_facets.size() << std::endl;
                //std::cout << "  Number of vertices in constructed patch: " << patch_vertices.size() << std::endl;
                //std::cout << "  Is fairing successful: " << success << std::endl;
                ++nb_holes;
            }
        }
    }
    catch (const std::exception& e)
    {
        outputErrorStr = "cgal error";
        return false;
    }
    catch (...)
    {
        outputErrorStr = "cgal error";
        return false;
    }
    
    return true;

}
int CreateCgalMesh::fillHoles(ccGenericPointCloud *cloud, std::vector<Facet> &facets,double max_hole_diam, 
    int max_num_hole_edges, std::string tempFile, std::string& outputErrorStr, int& percent)
{

    std::size_t pointCount = cloud->size();
    if (pointCount < 3)
    {
        outputErrorStr = "Not enough points";
        return false;
    }
    std::vector<Point_3> vertices;
    try
    {
        vertices.resize(pointCount);
    }
    catch (const std::bad_alloc&)
    {
        outputErrorStr = "Not enough memory";
        return false;
    };
    std::vector<Eigen::Matrix3d> vertColor(pointCount, Eigen::Matrix3d());
    cloud->placeIteratorAtBeginning();
    for (unsigned i = 0; i < pointCount; ++i)
    {
        const CCVector3* p = cloud->getPoint(i);
        vertices[i] = Point_3(p->x, p->y, p->z);
        if (cloud->hasColors())
        {
            const ccColor::Rgba p_color = cloud->getPointColor(i);
            vertColor.at(i)(0) = p_color.r;
            vertColor.at(i)(1) = p_color.g;
            vertColor.at(i)(2) = p_color.b;
        }
    }
    Mesh output_mesh;
    MeshType m_output;
    CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(vertices, facets, output_mesh);

    std::vector<halfedge_descriptor> border_cycles;
    // collect one halfedge per boundary cycle 
    PMP::extract_boundary_cycles(output_mesh, std::back_inserter(border_cycles));
    unsigned int nb_holes = 0;
    {
        max_num_hole_edges = 10000;
        for (halfedge_descriptor h : border_cycles)
        {
            if (max_hole_diam > 0 && max_num_hole_edges > 0 &&
                !is_small_hole(h, output_mesh, max_hole_diam, max_num_hole_edges))
                continue;
            ++nb_holes;
        }
    }
    {
        unsigned int count = 0;
        for (halfedge_descriptor h : border_cycles)
        {
            if (max_hole_diam > 0 && max_num_hole_edges > 0 &&
                !is_small_hole(h, output_mesh, max_hole_diam, max_num_hole_edges))
                continue;
            /*std::vector<face_descriptor>  patch_facets;
            std::vector<vertex_descriptor> patch_vertices;
            bool success = std::get<0>(PMP::triangulate_refine_and_fair_hole(output_mesh,
               h,std::back_inserter(patch_facets),std::back_inserter(patch_vertices)));*/
               /*bool success = std::get<0>(PMP::triangulate_refine_and_fair_hole(output_mesh,
                   h,
                   CGAL::Emptyset_iterator(), CGAL::Emptyset_iterator()));*/
                   /*std::get<0>(PMP::triangulate_and_refine_hole(output_mesh,
                       h, CGAL::Emptyset_iterator(), CGAL::Emptyset_iterator()));*/
            //PMP::triangulate_hole(output_mesh, h, CGAL::Emptyset_iterator());
            std::vector<face_descriptor>  patch_facets;
            std::vector<vertex_descriptor> patch_vertices;
            PMP::triangulate_refine_and_fair_hole(output_mesh, h, std::back_inserter(patch_facets), std::back_inserter(patch_vertices));
            ++count;
            percent = count * 100.0 / nb_holes;
        }
        std::map<Mesh::Vertex_index, int> vertex_to_int;
        int index = 0;
        std::vector<Point_3> fillhole_points;
        for (const auto &vertex: output_mesh.vertices())
        {
            vertex_to_int[vertex] = index++;
            const Point_3 &point = output_mesh.point(vertex);
            fillhole_points.push_back(point);
        }
        Eigen::MatrixXf vertMatrix;
        vertMatrix.resize(fillhole_points.size(), 3);
        for (size_t i = 0; i < fillhole_points.size(); ++i)
        {
            const Point_3 &p = fillhole_points[i];
            vertMatrix(i, 0) = p.x();
            vertMatrix(i, 1) = p.y();
            vertMatrix(i, 2) = p.z();
        }
        vcg::tri::Allocator<MeshType>::AddVertices(m_output, vertMatrix);
        for (size_t i = 0; i < m_output.vert.size(); i++)
        {
            m_output.vert[i].C() = vcg::Color4b(255, 255, 255, 255);
        }
        for (size_t i = 0; i < pointCount; i++)
        {
            m_output.vert[i].C() =
                    vcg::Color4b(vertColor[i](0), vertColor[i](1), vertColor[i](2), 255);
        }
        MeshType::FaceIterator f_ret =
                vcg::tri::Allocator<MeshType>::AddFaces(m_output, output_mesh.faces().size());
        for (const auto &face: output_mesh.faces())
        {
            auto halfedge = output_mesh.halfedge(face);
            std::vector<Mesh::Vertex_index> vertices;
            for (auto h = halfedge;; h = output_mesh.next(h))
            {
                vertices.push_back(output_mesh.source(h));
                if (h == output_mesh.prev(halfedge)) break;// Stop when we complete the loop
            }
            if (vertices.size() == 3)
            {
                auto v0 = vertices[0];
                auto v1 = vertices[1];
                auto v2 = vertices[2];
                int v0_retidx = vertex_to_int[v0];
                int v1_retidx = vertex_to_int[v1];
                int v2_retidx = vertex_to_int[v2];
                MeshType::VertexPointer ivp[3];
                ivp[0] = &m_output.vert[v0_retidx];
                ivp[1] = &m_output.vert[v1_retidx];
                ivp[2] = &m_output.vert[v2_retidx];
                (*&f_ret)->V(0) = ivp[0];
                (*&f_ret)->V(1) = ivp[1];
                (*&f_ret)->V(2) = ivp[2];
            }
            ++f_ret;
        }
        vcg::tri::UpdateColor<MeshType>::PerFaceFromVertex(m_output);
    }
    vcg::tri::io::ExporterOBJ<MeshType>::Save(m_output, tempFile.c_str(),vcg::tri::io::Mask::IOM_VERTCOLOR);
    percent = 100;
    return nb_holes;

}
