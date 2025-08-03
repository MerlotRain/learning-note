#pragma once

#include <glm/glm.hpp>
#include <limits.h>

template <typename T>
class RgbT
{
public:
    union
    {
        struct
        {
            T r, g, b;
        };
        T rgb[3];
    };

    constexpr inline RgbT() : r(0), g(0), b(0) {}
    constexpr inline RgbT(T red, T green, T blue) : r(red), g(green), b(blue) {}
    inline bool operator==(const RgbT &other) const { return r == other.r && g == other.g && b == other.b; }
};

using Rgb = RgbT<unsigned char>;
using Rgbf = RgbT<float>;

template <typename T>
class RgbaT
{
public:
    union
    {
        struct
        {
            T r, g, b, a;
        };
        T rgba[4];
    };

    constexpr inline RgbaT() : r(0), g(0), b(0), a(0) {}
    constexpr inline RgbaT(T red, T green, T blue, T alpha) : r(red), g(green), b(blue), a(alpha) {}
    inline bool operator==(const RgbaT &other) const { return r == other.r && g == other.g && b == other.b && a == other.a; }
};

using Rgba = RgbaT<unsigned char>;
using Rgbaf = RgbaT<float>;

constexpr Rgb whiteRGB(UCHAR_MAX, UCHAR_MAX, UCHAR_MAX);
constexpr Rgb lightGreyRGB(static_cast<unsigned char>(UCHAR_MAX * 8 / 10), static_cast<unsigned char>(UCHAR_MAX * 8 / 10), static_cast<unsigned char>(UCHAR_MAX * 8 / 10));
constexpr Rgb darkGreyRGB(UCHAR_MAX / 2, UCHAR_MAX / 2, UCHAR_MAX / 2);
constexpr Rgb redRGB(UCHAR_MAX, 0, 0);
constexpr Rgb greenRGB(0, UCHAR_MAX, 0);
constexpr Rgb blueRGB(0, 0, UCHAR_MAX);
constexpr Rgb blueCCRGB(0, static_cast<unsigned char>(UCHAR_MAX * 7 / 10), UCHAR_MAX);
constexpr Rgb darkBlueRGB(0, 0, UCHAR_MAX / 2);
constexpr Rgb magentaRGB(UCHAR_MAX, 0, UCHAR_MAX);
constexpr Rgb cyanRGB(0, UCHAR_MAX, UCHAR_MAX);
constexpr Rgb orangeRGB(UCHAR_MAX, UCHAR_MAX / 2, 0);
constexpr Rgb blackRGB(0, 0, 0);
constexpr Rgb yellowRGB(UCHAR_MAX, UCHAR_MAX, 0);

constexpr Rgba white(whiteRGB.r, whiteRGB.g, whiteRGB.b, UCHAR_MAX);
constexpr Rgba lightGrey(lightGreyRGB.r, lightGreyRGB.g, lightGreyRGB.b, UCHAR_MAX);
constexpr Rgba darkGrey(darkGreyRGB.r, darkGreyRGB.g, darkGreyRGB.b, UCHAR_MAX);
constexpr Rgba red(redRGB.r, redRGB.g, redRGB.b, UCHAR_MAX);
constexpr Rgba green(greenRGB.r, greenRGB.g, greenRGB.b, UCHAR_MAX);
constexpr Rgba blue(blueRGB.r, blueRGB.g, blueRGB.b, UCHAR_MAX);
constexpr Rgba blueCC(blueCCRGB.r, blueCCRGB.g, blueCCRGB.b, UCHAR_MAX);
constexpr Rgba darkBlue(darkBlueRGB.r, darkBlueRGB.g, darkBlueRGB.b, UCHAR_MAX);
constexpr Rgba magenta(magentaRGB.r, magentaRGB.g, magentaRGB.b, UCHAR_MAX);
constexpr Rgba cyan(cyanRGB.r, cyanRGB.g, cyanRGB.b, UCHAR_MAX);
constexpr Rgba orange(orangeRGB.r, orangeRGB.g, orangeRGB.b, UCHAR_MAX);
constexpr Rgba black(blackRGB.r, blackRGB.g, blackRGB.b, UCHAR_MAX);
constexpr Rgba yellow(yellowRGB.r, yellowRGB.g, yellowRGB.b, UCHAR_MAX);

constexpr Rgbaf bright(1.00f, 1.00f, 1.00f, 1.00f);
constexpr Rgbaf lighter(0.83f, 0.83f, 0.83f, 1.00f);
constexpr Rgbaf light(0.66f, 0.66f, 0.66f, 1.00f);
constexpr Rgbaf middle(0.50f, 0.50f, 0.50f, 1.00f);
constexpr Rgbaf dark(0.34f, 0.34f, 0.34f, 1.00f);
constexpr Rgbaf darker(0.17f, 0.17f, 0.17f, 1.00f);
constexpr Rgbaf darkest(0.08f, 0.08f, 0.08f, 1.00f);
constexpr Rgbaf night(0.00f, 0.00f, 0.00f, 1.00F);
constexpr Rgbaf defaultMeshFrontDiff(0.00f, 0.90f, 0.27f, 1.00f);
constexpr Rgbaf defaultMeshBackDiff(0.27f, 0.90f, 0.90f, 1.00f);

constexpr Rgb defaultBkgColor(10, 102, 151);                                     // dark blue
constexpr Rgba defaultColor(UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX);         // white
constexpr Rgba defaultLabelBkgColor(UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX); // white
constexpr Rgba defaultLabelMarkerColor(UCHAR_MAX, 0, UCHAR_MAX, UCHAR_MAX);      // magenta