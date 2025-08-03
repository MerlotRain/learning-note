#pragma once

#include "genericindexedcloudpersist.h"
#include <type_traits>
#include "boundingbox.h"

template <typename BaseClass, typename StringType = const char *>
class PointCloudT : public BaseClass
{
    static_assert(std::is_base_of_v<GenericIndexedCloudPersist, BaseClass>, "BaseClass must be a subclass of GenericIndexedCloudPersist");

public:
    PointCloudT();

protected:
    std::vector<glm::vec3> m_points;
    BoundingBox m_bbox;
};