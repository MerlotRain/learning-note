#pragma once

#include <map>
#include "colorscale.h"

class ColorScaleManager
{
public:
    static ColorScaleManager &instance();

    enum DefaultScale
    {
		BGYR              = 0,  /**< Blue-Green-Yellow-Red ramp (default for distances display) */
		GREY              = 1,  /**< Grey ramp (default for Global Illumination) */
		BWR               = 2,  /**< Blue-White-Red ramp (for signed SF)*/
		RY                = 3,  /**< Red-Yellow ramp */
		RW                = 4,  /**< Red-White ramp */
		ABS_NORM_GREY     = 5,  /**< Absolute normalized grey ramp (intensities between 0 and 1) */
		HSV_360_DEG       = 6,  /**< HSV colors between 0 and 360 degrees */
		VERTEX_QUALITY    = 7,  /**< Mesh vertex quality (see CCCoreLib::MeshSamplingTools::VertexFlags) */
		DIP_BRYW          = 8,  /**< Dip (0 - 90 degrees) (Brown-Red-Yellow-White) */
		DIP_DIR_REPEAT    = 9,  /**< Dip direction (0 - 360 degrees) */
		VIRIDIS           = 10, /**< matplotlib library colorscale created by Stéfan van der Walt and Nathaniel Smith */
		BROWN_YELLOW      = 11, /**< Brown-Yellow */
		YELLOW_BROWN      = 12, /**< Yellow-Brown */
		TOPO_LANDSERF     = 13, /**< Topo Landserf (quartile) */
		HIGH_CONTRAST     = 14, /**< High contrast */
		CIVIDIS           = 15, /**< matplotlib library colorscale - see https://arxiv.org/ftp/arxiv/papers/1712/1712.01662.pdf */
		ASPRS_CLASSES     = 16, /**< ASPRS classes */
		ASPRS_WITH_LABELS = 17, /**< ASPRS classes with labels */
    };

    void addScale(ColorScale::Shared scale);

protected:
    ColorScaleManager();
    static ColorScale::Shared create(DefaultScale type);

private:
    std::map<std::string, ColorScale::Shared> m_scales;
};