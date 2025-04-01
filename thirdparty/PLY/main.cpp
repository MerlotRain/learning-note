#include "rply.h"
#include <ccMesh.h>
#include <ccPointCloud.h>

struct BLHPoint
{
    double B;
    double L;
    double H;
};

static void ply_errorCallback(p_ply _ply, const char *message) { ccLog::Error("[PLY] '%s'", message); }

/*
use library rply write *.PLY format file.
* ply_create -- create a new ply object
* ply_add_element -- add base element ,common is vertex number and face number
* ply_add_scalar_property -- create scalar ,common is x, y, z, nx, ny, nz, and some from your custom settings.
* ply_add_comment -- and comment ,common is create by and create time.
* ply_write -- when write vertex, it will equal the number of scalar properties.
*/

void main()
{
    QString strPath = "...";
    ccMesh *mesh = nullptr;
    ccGenericPointCloud *cloud = nullptr;
    std::vector<BLHPoint> blh_points;

#ifdef _WIN32
    p_ply ply = ply_create(strPath.toStdWString().c_str(), PLY_ASCII, ply_errorCallback, 0, NULL);
#else
    p_ply ply = ply_create(strPath.toStdString().c_str(), PLY_ASCII, ply_errorCallback, 0, NULL);
#endif
    if (!ply) return;

    int result = 1;
    e_ply_type coordType = cloud->isShifted() || sizeof(PointCoordinateType) > 4 ? PLY_DOUBLE : PLY_FLOAT;
    if (ply_add_element(ply, "vertex", cloud->size()))
    {
        result = ply_add_scalar_property(ply, "x", coordType);
        result = ply_add_scalar_property(ply, "y", coordType);
        result = ply_add_scalar_property(ply, "z", coordType);
    }
    else
    {
        result = 0;
    }

    if (cloud->hasNormals())
    {
        result = ply_add_scalar_property(ply, "nx", coordType);
        result = ply_add_scalar_property(ply, "ny", coordType);
        result = ply_add_scalar_property(ply, "nz", coordType);
    }
    result = ply_add_scalar_property(ply, "lat", PLY_DOUBLE);
    result = ply_add_scalar_property(ply, "lon", PLY_DOUBLE);

    unsigned int tri_num = mesh->size();
    if (tri_num > 0 && ply_add_element(ply, "face", tri_num))
    {
        ply_add_list_property(ply, "vertex_indices", PLY_UCHAR, PLY_INT);
    }

    ply_add_comment(ply, "Creat By FJDynamics Trion Model");
    QString createTime = QString("Create %1").arg(QDateTime::currentDateTime().toString(Qt::ISODate));
    ply_add_comment(ply, createTime.toStdString().c_str());

    // write header
    if (!ply_write_header(ply))
    {
        ply_close(ply);
        return;
    }

    for (int i = 0; i < cloud->size(); ++i)
    {
        const CCVector3 *P = cloud->getPoint(i);
        CCVector3d Pglobal = cloud->toGlobal3d<PointCoordinateType>(*P);
        ply_write(ply, Pglobal.x);
        ply_write(ply, Pglobal.y);
        ply_write(ply, Pglobal.z);
        if (cloud->hasNormals())
        {
            const CCVector3 &N = cloud->getPointNormal(i);
            ply_write(ply, static_cast<double>(N.x));
            ply_write(ply, static_cast<double>(N.y));
            ply_write(ply, static_cast<double>(N.z));
        }
        ply_write(ply, static_cast<double>(blh_points.at(i).B));
        ply_write(ply, static_cast<double>(blh_points.at(i).L));
    }

    mesh->placeIteratorAtBeginning();
    for (unsigned i = 0; i < tri_num; ++i)
    {
        const CCCoreLib::VerticesIndexes *tsi = mesh->getNextTriangleVertIndexes();
        ply_write(ply, double(3));
        assert(tsi->i1 < vertCount);
        assert(tsi->i2 < vertCount);
        assert(tsi->i3 < vertCount);
        ply_write(ply, double(tsi->i1));
        ply_write(ply, double(tsi->i2));
        ply_write(ply, double(tsi->i3));
    }

    ply_close(ply);
}