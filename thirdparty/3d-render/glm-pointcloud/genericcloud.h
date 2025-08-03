#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <functional>

class GenericCloud
{
public:
    GenericCloud() = default;
    virtual ~GenericCloud() = default;

    virtual size_t size() const = 0;
    virtual void forEach(std::function<void(const glm::vec3&, double)> callback) = 0;
    virtual void getBoundingBox(glm::vec3& min, glm::vec3& max) const = 0;
    virtual unsigned char testVisiblity(const glm::vec3& point) const = 0;
    virtual void placeIteratorAtBeginning() = 0;
    virtual const glm::vec3* getNextPoint() = 0;
    virtual bool enableScalarField() = 0;
    virtual bool isScalarFieldEnabled() const = 0;
    virtual void setPointScalarValue(unsigned pointIndex, double value) = 0;
    virtual double getPointScalarValue(unsigned pointIndex) const = 0;
};