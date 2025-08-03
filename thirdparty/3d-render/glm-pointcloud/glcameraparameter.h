#pragma once

#include <glm/glm.hpp>
#include <limits>

struct GLCameraParameter
{
    glm::mat4 modelViewMat;   // View matrix
    glm::mat4 projectionMat;  // Projection matrix
    int viewport[4];          // Viewport dimensions: x, y, width, height
    bool perspective;         // True if perspective projection, false if orthographic
    float fov;                // Field of view (in degrees)
    double pixelSize;         // Size of a pixel in the camera's coordinate system
    double nearClippingDepth; // Near clipping plane distance
    double farClippingDepth;  // Far clipping plane distance

    GLCameraParameter();
    bool project(const glm::vec3 &input, glm::vec3 &output, bool *inFrustum = nullptr) const;
    bool unproject(const glm::vec3 &input, glm::vec3 &output) const;
    bool operator==(const GLCameraParameter &other) const;
};