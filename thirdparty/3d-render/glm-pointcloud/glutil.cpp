#include "glutil.h"

/**
 * @brief Calculate the inverse of a 4x4 matrix.
 *
 * @param m
 * @param out
 * @return true
 * @return false
 */
bool GLUtil::inverse(const glm::mat4 &m, glm::mat4 &out)
{
    double wtmp[4][8];
    double m0, m1, m2, m3, s;
    double *r0, *r1, *r2, *r3;
    r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

    r0[0] = m[0][0];
    r0[1] = m[0][1];
    r0[2] = m[0][2];
    r0[3] = m[0][3];
    r0[4] = 1.0;
    r0[5] = r0[6] = r0[7] = 0.0;
    r1[0] = m[1][0];
    r1[1] = m[1][1];
    r1[2] = m[1][2];
    r1[3] = m[1][3];
    r1[5] = 1.0;
    r1[4] = r1[6] = r1[7] = 0.0;
    r2[0] = m[2][0];
    r2[1] = m[2][1];
    r2[2] = m[2][2];
    r2[3] = m[2][3];
    r2[6] = 1.0;
    r2[4] = r2[5] = r2[7] = 0.0;
    r3[0] = m[3][0];
    r3[1] = m[3][1];
    r3[2] = m[3][2];
    r3[3] = m[3][3];
    r3[7] = 1.0;
    r3[4] = r3[5] = r3[6] = 0.0;

    // choose pivot - or die
    if (std::abs(r3[0]) > std::abs(r2[0]))
        std::swap(r3, r2);
    if (std::abs(r2[0]) > std::abs(r1[0]))
        std::swap(r2, r1);
    if (std::abs(r1[0]) > std::abs(r0[0]))
        std::swap(r1, r0);
    if (0.0 == r0[0])
        return false;

    // eliminate first variable
    m1 = r1[0] / r0[0];
    m2 = r2[0] / r0[0];
    m3 = r3[0] / r0[0];
    s = r0[1];
    r1[1] -= m1 * s;
    r2[1] -= m2 * s;
    r3[1] -= m3 * s;
    s = r0[2];
    r1[2] -= m1 * s;
    r2[2] -= m2 * s;
    r3[2] -= m3 * s;
    s = r0[3];
    r1[3] -= m1 * s;
    r2[3] -= m2 * s;
    r3[3] -= m3 * s;
    s = r0[4];
    if (s != 0.0)
    {
        r1[4] -= m1 * s;
        r2[4] -= m2 * s;
        r3[4] -= m3 * s;
    }
    s = r0[5];
    if (s != 0.0)
    {
        r1[5] -= m1 * s;
        r2[5] -= m2 * s;
        r3[5] -= m3 * s;
    }
    s = r0[6];
    if (s != 0.0)
    {
        r1[6] -= m1 * s;
        r2[6] -= m2 * s;
        r3[6] -= m3 * s;
    }
    s = r0[7];
    if (s != 0.0)
    {
        r1[7] -= m1 * s;
        r2[7] -= m2 * s;
        r3[7] -= m3 * s;
    }

    // choose pivot - or die
    if (std::abs(r3[1]) > std::abs(r2[1]))
        std::swap(r3, r2);
    if (std::abs(r2[1]) > std::abs(r1[1]))
        std::swap(r2, r1);
    if (0.0 == r1[1])
        return false;

    // eliminate second variable
    m2 = r2[1] / r1[1];
    m3 = r3[1] / r1[1];
    r2[2] -= m2 * r1[2];
    r3[2] -= m3 * r1[2];
    r2[3] -= m2 * r1[3];
    r3[3] -= m3 * r1[3];
    s = r1[4];
    if (0.0 != s)
    {
        r2[4] -= m2 * s;
        r3[4] -= m3 * s;
    }
    s = r1[5];
    if (0.0 != s)
    {
        r2[5] -= m2 * s;
        r3[5] -= m3 * s;
    }
    s = r1[6];
    if (0.0 != s)
    {
        r2[6] -= m2 * s;
        r3[6] -= m3 * s;
    }
    s = r1[7];
    if (0.0 != s)
    {
        r2[7] -= m2 * s;
        r3[7] -= m3 * s;
    }

    // choose pivot - or die
    if (std::abs(r3[2]) > std::abs(r2[2]))
        std::swap(r3, r2);
    if (0.0 == r2[2])
        return false;

    // eliminate third variable
    m3 = r3[2] / r2[2];
    r3[3] -= m3 * r2[3];
    r3[4] -= m3 * r2[4];
    r3[5] -= m3 * r2[5];
    r3[6] -= m3 * r2[6];
    r3[7] -= m3 * r2[7];

    // last check
    if (0.0 == r3[3])
        return false;

    s = 1.0 / r3[3]; // now back substitute row 3
    r3[4] *= s;
    r3[5] *= s;
    r3[6] *= s;
    r3[7] *= s;
    m2 = r2[3]; // now back substitute row 2
    s = 1.0 / r2[2];
    r2[4] = s * (r2[4] - r3[4] * m2);
    r2[5] = s * (r2[5] - r3[5] * m2);
    r2[6] = s * (r2[6] - r3[6] * m2);
    r2[7] = s * (r2[7] - r3[7] * m2);
    m1 = r1[3];
    r1[4] -= r3[4] * m1;
    r1[5] -= r3[5] * m1;
    r1[6] -= r3[6] * m1;
    r1[7] -= r3[7] * m1;
    m0 = r0[3];
    r0[4] -= r3[4] * m0;
    r0[5] -= r3[5] * m0;
    r0[6] -= r3[6] * m0;
    r0[7] -= r3[7] * m0;
    m1 = r1[2]; // now back substitute row 1
    s = 1.0 / r1[1];
    r1[4] = s * (r1[4] - r2[4] * m1);
    r1[5] = s * (r1[5] - r2[5] * m1);
    r1[6] = s * (r1[6] - r2[6] * m1);
    r1[7] = s * (r1[7] - r2[7] * m1);
    m0 = r0[2];
    r0[4] -= r2[4] * m0;
    r0[5] -= r2[5] * m0;
    r0[6] -= r2[6] * m0;
    r0[7] -= r2[7] * m0;
    m0 = r0[1]; // now back substitute row 0
    s = 1.0 / r0[0];
    r0[4] = s * (r0[4] - r1[4] * m0);
    r0[5] = s * (r0[5] - r1[5] * m0);
    r0[6] = s * (r0[6] - r1[6] * m0);
    r0[7] = s * (r0[7] - r1[7] * m0);

    out[0][0] = r0[4];
    out[0][1] = r0[5];
    out[0][2] = r0[6];
    out[0][3] = r0[7];
    out[1][0] = r1[4];
    out[1][1] = r1[5];
    out[1][2] = r1[6];
    out[1][3] = r1[7];
    out[2][0] = r2[4];
    out[2][1] = r2[5];
    out[2][2] = r2[6];
    out[2][3] = r2[7];
    out[3][0] = r3[4];
    out[3][1] = r3[5];
    out[3][2] = r3[6];
    out[3][3] = r3[7];
}

/**
 * @brief Project a 3D point into 2D screen coordinates.
 *
 * @param input
 * @param modelView
 * @param projection
 * @param viewport
 * @param output
 * @param inFrustum
 * @param nearClippingDepth
 * @param farClippingDepth
 * @return true
 * @return false
 */
bool GLUtil::project(const glm::vec3 &input, const glm::mat4 &modelView, const glm::mat4 &projection,
                     const int *viewport, glm::vec3 &output, bool *inFrustum, const double *nearClippingDepth, const double *farClippingDepth)
{
    // model view transform
    glm::vec4 pm = modelView * glm::vec4(input, 1.0f);
    // projection transform
    glm::vec4 pp = projection * pm;

    if (pp.w == 0.0f)
    {
        return false; // Avoid division by zero
    }

    // perspective division
    pp.x /= pp.w;
    pp.y /= pp.w;
    pp.z /= pp.w;

    output.x = (pp.x + 1.0f) * 0.5f; // Convert to normalized device coordinates
    output.y = (pp.y + 1.0f) * 0.5f;

    if (inFrustum)
    {
        // Check if the point is inside the frustum
        if (nearClippingDepth && -pm.z < *nearClippingDepth)
            *inFrustum = false;
        else if (farClippingDepth && -pm.z > *farClippingDepth)
            *inFrustum = false;
        else
            *inFrustum = (std::abs(pp.x) <= 1.0 && std::abs(pp.y) <= 1.0 && std::abs(pp.z) <= 1.0);
    }

    // Window coordinates
    // Map x, y to range 0-1
    output.x = (1.0 + pp.x) / 2 * viewport[2] + viewport[0];
    output.y = (1.0 + pp.y) / 2 * viewport[3] + viewport[1];
    // This is only correct when glDepthRange(0.0, 1.0)
    output.z = (1.0 + pp.z) / 2; // Between 0 and 1

    return true;
}

/**
 * @brief Unproject a 2D screen coordinate back into 3D world coordinates.
 *
 * @param input
 * @param modelView
 * @param projection
 * @param viewport
 * @param output
 * @return true
 * @return false
 */
bool GLUtil::unproject(const glm::vec3 &input, const glm::mat4 &modelView, const glm::mat4 &projection, const int *viewport, glm::vec3 &output)
{
    glm::mat4 A = projection * modelView;
    glm::mat4 m;

    if (!inverse(A, m))
    {
        return false; // Inversion failed
    }

    glm::mat4 mA = m * A;

    // transformation of normalized coordinates between -1 and 1
    glm::vec4 in;
    in.x = (input.x - viewport[0]) / viewport[2] * 2.0f - 1.0f;
    in.y = (input.y - viewport[1]) / viewport[3] * 2.0f - 1.0f;
    in.z = input.z * 2.0f - 1.0f; // Assuming input.z is in range [0, 1]
    in.w = 1.0f;

    // objects coordinates
    glm::vec4 out = m * in;
    if (out.w = 0.0f)
    {
        return false; // Avoid division by zero
    }

    output.x = out.x / out.w;
    output.y = out.y / out.w;
    output.z = out.z / out.w;
    return true;
}