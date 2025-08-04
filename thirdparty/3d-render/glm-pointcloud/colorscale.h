#pragma once

#include <memory>
#include <string>
#include <set>
#include <vector>
#include <glm/glm.hpp>

struct ColorScaleElement
{
    double relativePos;
    glm::vec3 color;

    static bool isSmaller(const ColorScaleElement &a1, const ColorScaleElement &a2)
    {
        return a1.relativePos < a2.relativePos;
    }
};

class ColorScale
{
public:
    struct Label
    {
        double value = 0.0;
        std::string text;
        bool operator<(const Label &other) const { return value < other.value; }
    };

    using Shared = std::shared_ptr<ColorScale>;

    static Shared create(const std::string &name);

    ColorScale(const std::string &name, const std::string &uuid = std::string());
    ~ColorScale();

    static constexpr auto min_stpes = 2;
    static constexpr auto default_stpes = 256;
    static constexpr auto max_stpes = 1024;

private:
    std::string m_name;
    std::string m_uuid;
    std::vector<ColorScaleElement> m_steps;
    glm::vec3 m_rgbaScale[max_stpes];
    bool m_updated;
    bool m_relative;
    bool m_locked;
    double m_absoluteMinValue;
    double m_absoluteRange;
    std::set<Label> m_customLabels;
};