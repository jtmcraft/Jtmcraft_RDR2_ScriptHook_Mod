#include "debug_screen.h"

#include <sstream>

#include "../../inc/natives.h"
#include "../data/configuration.h"
#include "../util/camera_util.h"
#include "../util/graphics.h"
#include "../util/util.h"

void debug_screen::show_background(const bool show_position_vector, const bool show_camera_pointing_at) {
    static constexpr float rect_left = 0.005f;
    static constexpr float rect_top = 0.005f;
    static constexpr float rect_width = 0.205f;
    static constexpr float rect_height = 0.045f;
    static ui_rectangle rectangle(rect_left, rect_top, rect_width, rect_height);

    static constexpr byte color_red = 66;
    static constexpr byte color_green = 66;
    static constexpr byte color_blue = 66;
    static constexpr byte color_alpha = 190;
    static ui_color color(color_red, color_green, color_blue, color_alpha);

    graphics_util::draw_rectangle(rectangle, color);
}

void debug_screen::show_player_position_details(const std::string& player_details, const float y) {
    graphics_util::draw_text(player_details, 0.01f, y);
}

bool debug_screen::is_valid_direction_index(const int index) {
    return index >= 0 && index < number_of_directions;
}

std::string debug_screen::get_cardinal_direction(const float heading) {
    if (heading < 0) {
        return "";
    }

    const int index = static_cast<int>(heading / angle_per_cardinal_direction);

    if (!is_valid_direction_index(index)) {
        return "";
    }

    return cardinal_directions[index];
}

void debug_screen::show_player_position(const bool show_position_vector, const bool show_camera_pointing_at) {
    const Ped player_ped = PLAYER::PLAYER_PED_ID();
    std::stringstream stream;

    if (show_position_vector) {
        const Vector3 player_coords = ENTITY::GET_ENTITY_COORDS(player_ped, true, 0);
        const float player_heading = ENTITY::GET_ENTITY_HEADING(player_ped);
        
        stream << util::format_coords(player_coords) << "; "
            << util::format_float_value(player_heading) << " ("
            << get_cardinal_direction(player_heading) << ")"
            << '\n';
    }

    if (show_camera_pointing_at) {
        const Vector3& pointing_at = camera_util::pointing_at(CAM::GET_GAMEPLAY_CAM_COORD(), 10.0f);
        stream << util::format_coords(pointing_at);
    }

    const bool show_both = show_position_vector && show_camera_pointing_at;
    const float y = show_both ? 0.012f : 0.02f;
    show_player_position_details(stream.str(), y);
}