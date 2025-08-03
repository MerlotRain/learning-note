#pragma once

#include <glm/glm.hpp>

class BoundingBox
{
    glm::vec3 m_min;
    glm::vec3 m_max;
    bool m_valid;

public:
    BoundingBox() : m_min(0, 0, 0), m_max(0, 0, 0), m_valid(false) {}
    BoundingBox(const glm::vec3 &min, const glm::vec3 &max, bool valid) : m_min(min), m_max(max), m_valid(valid) {}

    BoundingBox operator+(const BoundingBox &other) const;
    const BoundingBox &operator+=(const BoundingBox &other);
    const BoundingBox &operator+=(const glm::vec3 &v);
    const BoundingBox &operator-=(const glm::vec3 &v);
    const BoundingBox &operator*=(float scale);

    void clear();
    void add(const glm::vec3 &v);

    const glm::vec3 &getMin() const { return m_min; }
    glm::vec3 &getMin() { return m_min; }
    const glm::vec3 &getMax() const { return m_max; }
    glm::vec3 &getMax() { return m_max; }
    bool isValid() const { return m_valid; }
    glm::vec3 getCenter() const;
    glm::vec3 getDiagVec() const;
    double getDiagNorm() const;
    double getDiagNormd() const;
};