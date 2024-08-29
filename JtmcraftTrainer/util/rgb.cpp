#include "rgb.h"

namespace rgb_util {
    constexpr float max_hue = 360.0f;
    constexpr float max_rgb_value = 255.0f;
    constexpr float slice_size = 60.0f;

    void compute_hsb_color_components(const float brightness, const float saturation, const int slice, const float hue_fraction, float& red, float& green, float& blue) {
        const float a = brightness * (1.0f - saturation);
        const float b = brightness * (1.0f - saturation * hue_fraction);
        const float c = brightness * (1.0f - saturation * (1.0f - hue_fraction));

        switch(slice) {
        case 0:
            red = brightness;
            green = c;
            blue = a;
            break;
        case 1:
            red = b;
            green = brightness;
            blue = a;
            break;
        case 2:
            red = a;
            green = brightness;
            blue = c;
            break;
        case 3:
            red = a;
            green = b;
            blue = brightness;
            break;
        case 4:
            red = c;
            green = a;
            blue = brightness;
            break;
        case 5:
            red = brightness;
            green = a;
            blue = b;
            break;
        default:
            red = 0.0f;
            green = 0.0f;
            blue = 0.0f;
            break;
        }
    }

    void from_hsb(float hue, const float saturation, const float brightness, int* p_red, int* p_green, int* p_blue) {
        float red = 0.0f;
        float green = 0.0f;
        float blue = 0.0f;

        if (saturation == 0.0f) {
            red = green = blue = brightness;
        } else {
            if (hue >= max_hue) {
                hue = 0;
            }
            const int slice = static_cast<int>(hue / slice_size);
            const float hue_fraction = hue / slice_size - static_cast<float>(slice);
            compute_hsb_color_components(brightness, saturation, slice, hue_fraction, red, green, blue);
        }
        
        *p_red = static_cast<int>(red * max_rgb_value);
        *p_green = static_cast<int>(green * max_rgb_value);
        *p_blue = static_cast<int>(blue * max_rgb_value);
    }
}
