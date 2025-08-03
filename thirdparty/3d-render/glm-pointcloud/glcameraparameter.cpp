#include "glcameraparameter.h"
#include "glutil.h"

GLCameraParameter::GLCameraParameter() : modelViewMat(0.0f), projectionMat(0.0f), viewport{0, 0, 0, 0}, perspective(false), fov(0.0f), pixelSize(0.0), nearClippingDepth(std::numeric_limits<double>::quiet_NaN()), farClippingDepth(std::numeric_limits<double>::quiet_NaN()) {}

/**
 * @brief Project a 3D point into 2D screen coordinates.
 *
 * @param input
 * @param output
 * @param inFrustum
 * @return true
 * @return false
 */
bool GLCameraParameter::project(const glm::vec3 &input, glm::vec3 &output, bool *inFrustum = nullptr) const
{
    return GLUtil::project(input, modelViewMat, projectionMat, viewport, output, inFrustum, (inFrustum && !std::isnan(nearClippingDepth)) ? &nearClippingDepth : nullptr, (inFrustum && !std::isnan(farClippingDepth)) ? &farClippingDepth : nullptr);
}

/**
 * @brief Unproject a 2D screen coordinate back into 3D world coordinates.
 *
 * @param input
 * @param output
 * @return true
 * @return false
 */
bool GLCameraParameter::unproject(const glm::vec3 &input, glm::vec3 &output) const
{
    return GLUtil::unproject(input, modelViewMat, projectionMat, viewport, output);
}

bool GLCameraParameter::operator==(const GLCameraParameter &other) const
{
    return modelViewMat == other.modelViewMat &&
           projectionMat == other.projectionMat &&
           viewport[0] == other.viewport[0] &&
           viewport[1] == other.viewport[1] &&
           viewport[2] == other.viewport[2] &&
           viewport[3] == other.viewport[3] &&
           perspective == other.perspective &&
           fov == other.fov &&
           pixelSize == other.pixelSize &&
           nearClippingDepth == other.nearClippingDepth &&
           farClippingDepth == other.farClippingDepth;
}