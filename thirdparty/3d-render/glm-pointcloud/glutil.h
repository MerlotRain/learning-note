#pragma once

#include <glm/glm.hpp>

class GLUtil
{
public:
    static bool inverse(const glm::mat4 &m, glm::mat4 &out);
    static bool project(const glm::vec3 &input, const glm::mat4 &modelView, const glm::mat4 &projection,
                        const int *viewport, glm::vec3 &output, bool *inFrustum = nullptr,
                        const double *nearClippingDepth = nullptr, const double *farClippingDepth = nullptr);
    static bool unproject(const glm::vec3 &input, const glm::mat4 &modelView, const glm::mat4 &projection,
                          const int *viewport, glm::vec3 &output);
};