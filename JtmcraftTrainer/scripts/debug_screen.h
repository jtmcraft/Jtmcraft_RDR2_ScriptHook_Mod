#pragma once
#include <array>
#include <string>

namespace debug_screen {
    constexpr int number_of_directions = 32;
    constexpr float angle_per_cardinal_direction = 360.0 / number_of_directions;
    
    static const std::array<std::string, 32> cardinal_directions = {
        "N", "NbW", "NNW", "NWbN", "NW", "NWbW", "WNW", "WbN",
        "W", "WbS", "WSW", "SWbW", "SW", "SWbS", "SSW", "SbW",
        "S", "SbE", "SSE", "SEbS", "SE", "SEbE", "ESE", "EbS",
        "E", "EbN", "ENE", "NEbE", "NE", "NEbN", "NNE", "NbE"
    };
    
    void show_background(bool show_position_vector, bool show_camera_pointing_at);
    void show_player_position_details(const std::string& player_details, float y);
    bool is_valid_direction_index(int index);
    std::string get_cardinal_direction(float heading);
    void show_player_position(bool show_position_vector, bool show_camera_pointing_at);
}
