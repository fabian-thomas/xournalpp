/*
 * Xournal++
 *
 * This file is part of the Xournal UnitTests
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#include <gtest/gtest.h>

#include "Color.h"

using namespace std;

bool operator==(GdkRGBA const& lhs, GdkRGBA const& rhs) noexcept {
    auto tieer = [](GdkRGBA const& val) { return std::tie(val.red, val.blue, val.green, val.alpha); };
    return tieer(lhs) == tieer(rhs);
}

std::ostream& operator<<(std::ostream& os, GdkRGBA const& val) {
    return os << "GdkRGBA{" << val.red << "," << val.green << "," << val.blue << "," << val.alpha << "}";
}


TEST(UtilColor, testColorToRGB) {
    auto color1 = 0U;
    auto color2 = 0xffffffU;
    auto color3 = 0x7f7f7fU;
    auto color4 = 0x808080U;
    auto rgb1 = GdkRGBA{0.0, 0.0, 0.0, 1.0};
    auto rgb2 = GdkRGBA{1, 1, 1, 1.0};
    auto rgb3 = GdkRGBA{0.5, 0.5, 0.5, 1.0};
    auto rgb_t1 = Util::rgb_to_GdkRGBA(color1);
    EXPECT_EQ(rgb1, rgb_t1);
    auto rgb_t2 = Util::rgb_to_GdkRGBA(color2);
    EXPECT_EQ(rgb2, rgb_t2);
    auto rgb_t4 = Util::rgb_to_GdkRGBA(color4);
    auto rgb_t3 = Util::rgb_to_GdkRGBA(color3);
    auto rgb_t5 = GdkRGBA{(rgb_t3.red + rgb_t4.red) / 2, (rgb_t3.green + rgb_t4.green) / 2,
                          (rgb_t3.blue + rgb_t4.blue) / 2, 1};
    EXPECT_EQ(rgb3, rgb_t5);
}

TEST(UtilColor, testColorToRGBAndBack) {
    for (size_t i = 0; i < 256; ++i) {
        Color color = i << 16U | i << 8U | i;
        Color color2 = color | i << 24U;
        EXPECT_EQ(color, Util::GdkRGBA_to_rgb(Util::rgb_to_GdkRGBA(color)));
        EXPECT_EQ(color2, Util::GdkRGBA_to_argb(Util::argb_to_GdkRGBA(color2)));
    }
}
