#pragma once
#include "../../../inc/types.h"
#include <unordered_map>
#include <string>
#include <vector>

struct cinematic_clock {
    int hour;
    int minute;
    int second;
};

struct script_camera {
    Vector3 start_position;
    Vector3 point_cam_at;
    bool rotate_instead_of_point;
    Vector3 end_position;
    cinematic_clock start_time;
    std::string text;
    Cam cam;
    Cam finish_cam;
};

struct cinematic {
    std::string music_event;
    std::unordered_map<int, script_camera> cameras;
};

struct script_cinematic_config {
    bool debug = true;
    std::unordered_map<std::string, cinematic> cinematics;
};

namespace camera_util {
    script_cinematic_config get_cinematics_config(const std::string& cinematic_name);
    void play_cinematic(const std::string& cinematic_name);
    Vector3 pointing_at(const Vector3& position, float distance);
    bool ray_cast(float distance, Entity* entity_hit);
    bool get_entity_free_aiming_at(Entity* entity);
    void fade_in(int fade_time);
    void fade_out(int fade_time);
}
