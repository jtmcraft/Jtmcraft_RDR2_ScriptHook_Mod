#include "graphics.h"

#include <string>
#include <vector>

#include "util.h"
#include "../../../inc/natives.h"
#include "../data/global_values.h"

const ui_color ui_color::black_opaque = { 0, 0, 0, 255 };
const ui_color ui_color::red_opaque = {255, 0, 0, 255};
const ui_color ui_color::white_opaque = {255, 255, 255, 255};

void graphics_util::draw_text(const std::string& text, const float x, const float y) {
    UI::SET_TEXT_SCALE(0.0, 0.25f);
    UI::SET_TEXT_COLOR_RGBA(255, 255, 255, 255);
    UI::SET_TEXT_CENTRE(0);
    UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
    UI::DRAW_TEXT(util::create_string(text), x, y);
}

void graphics_util::draw_center_text(const std::string& text) {
    const char* text_with_font = util::create_string("<FONT FACE='$body'>" + text + "</FONT>");
    UI::SET_TEXT_SCALE(0.55f, 0.55f);
    UI::SET_TEXT_COLOR_RGBA(255, 255, 255, 255);
    UI::SET_TEXT_CENTRE(1);
    UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
    invoke<Void>(0x16794E044C9EFB58, text_with_font, 0.5, 0.5);
    // UI::DRAW_TEXT(util::color_string(text_with_font), 0.5, 0.5);
}

float graphics_util::calculate_aligned_x(const float screen_x, const alignment text_align) {
    float x = screen_x / global_values::get_instance().get_screen_width();
    
    if (text_align == alignment::right) {
        x = 0.0f;
    } else if (text_align == alignment::center) {
        x = -1.0f + (x * 2.0f);
    }

    return x;
}

void graphics_util::draw_center_text(const std::string& text, const int font_size, const float screen_x, const float screen_y, const ui_color& color, font font) {
    const std::string selected_font = font_list[static_cast<int>(font)];
    const float x = calculate_aligned_x(screen_x, alignment::center);
    const float y = screen_y / global_values::get_instance().get_screen_height();
    const std::string size_string = std::to_string(font_size);
    const std::string formatted_text = "<TEXTFORMAT RIGHTMARGIN='0'><P ALIGN='Center'><FONT FACE='$" + selected_font + "' LETTERSPACING='0' SIZE='" + size_string + "'>~s~" + text + "</FONT></P><TEXTFORMAT>";

    UI::SET_TEXT_DROPSHADOW(5, ui_color::black_opaque.red, ui_color::black_opaque.green, ui_color::black_opaque.blue, ui_color::black_opaque.alpha);
    invoke<Void>(0x16FA5CE47F184F1E, color.red, color.green, color.blue, color.alpha);
    invoke<Void>(0x16794E044C9EFB58, formatted_text.c_str(), x, y);
}

void graphics_util::wait_and_draw_center_text(const int millis, const std::string& text, const ui_color& color) {
    const DWORD time_to_wait = GetTickCount() + millis;
    bool stop_waiting = false;

    const float x = global_values::get_instance().get_screen_width() / 2.0f;
    const float y = global_values::get_instance().get_screen_height() / 2.0f;
    
    while (GetTickCount() < time_to_wait || !stop_waiting) {
        WAIT(0);
        stop_waiting = true;
        draw_center_text(text, 45, x, y, color, font::font5);
    }
}

void graphics_util::draw_rectangle(const float line_left, const float line_top, const float width, const float height, const int red, const int green, const int blue, const int alpha) {
    GRAPHICS::DRAW_RECT((line_left + (width * 0.5f)), (line_top + (height * 0.5f)), width, height, red, green, blue, alpha, 0, 0);
}

void graphics_util::draw_rectangle(const ui_rectangle& rectangle, const ui_color& color) {
    draw_rectangle(rectangle.left, rectangle.top, rectangle.width, rectangle.height, color.red, color.green, color.blue, color.alpha);
}

void graphics_util::set_entity_light_color(const Entity entity, const int red, const int green, const int blue) {
    GRAPHICS::_0x6EC2A67962296F49(entity, red, green, blue);
    GRAPHICS::_ENTITY_DESCRIPTION_TEXT(entity);
}

void graphics_util::set_entity_light_intensity(const Entity entity, const float intensity) {
    GRAPHICS::_0x07C0F87AAC57F2E4(entity, intensity);
    GRAPHICS::_ENTITY_DESCRIPTION_TEXT(entity);
}

void graphics_util::draw_light(const Vector3& coords, const ui_color& color, const float range, const float intensity) {
    GRAPHICS::DRAW_LIGHT_WITH_RANGE(coords.x, coords.y, coords.z, color.red, color.green, color.blue, range, intensity);
}

void graphics_util::draw_light(const Vector3& coords, const float range, const float intensity) {
    draw_light(coords, ui_color::white_opaque, range, intensity);
}
