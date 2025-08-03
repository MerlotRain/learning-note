#pragma once

#include "genericIndexedcloud.h"

class GenericIndexedCloudPersist : public GenericIndexedCloud
{
public:
    GenericIndexedCloudPersist() = default;
    virtual ~GenericIndexedCloudPersist() override = default;
    virtual const glm::vec3 *getPointPersistentPtr(size_t index) const = 0;
};