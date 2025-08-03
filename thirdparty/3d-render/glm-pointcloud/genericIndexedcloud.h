#pragma once

#include "genericcloud.h"

class GenericIndexedCloud : public GenericCloud
{
public:
    GenericIndexedCloud() = default;
    virtual ~GenericIndexedCloud() override = default;

    virtual const glm::vec3 *getPoint(size_t index) const = 0;
    virtual void getPoint(size_t index, glm::vec3 &point) const = 0;
    virtual bool normalsAvailable() const { return false; }
    const glm::vec3 *getNormal(unsigned index) const { return nullptr; }
};