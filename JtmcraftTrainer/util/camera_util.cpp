#include "camera_util.h"

#include <fstream>
#include <map>
#include "entity.h"
#include "graphics.h"
#include "logger.h"
#include "math.h"
#include "../json.h"
#include "../../inc/natives.h"

script_camera create_script_camera(const float start_x, const float start_y, const float start_z,
                                   const float point_x, const float point_y, const float point_z,
                                   const bool rotate_instead,
                                   const float end_x, const float end_y, const float end_z,
                                   const std::string& camera_text,
                                   const int hour, const int minute, const int second) 
{
    script_camera cam;
    cam.start_position = {start_x, start_y, start_z};
    cam.point_cam_at = {point_x, point_y, point_z};
    cam.rotate_instead_of_point = rotate_instead;
    cam.end_position = {end_x, end_y, end_z};
    cam.text = camera_text;
    cam.cam = -1;
    cam.finish_cam = -1;
    return cam;
}

script_camera create_camera_from_config(nlohmann::json config) 
{
    script_camera cam;
    cam.start_position = { config["start_position"]["x"], config["start_position"]["y"], config["start_position"]["z"] };
    cam.point_cam_at = { config["point_cam_at"]["x"], config["point_cam_at"]["y"], config["point_cam_at"]["z"] };
    cam.rotate_instead_of_point = config["rotate_instead_of_point"];
    cam.end_position = { config["end_position"]["x"], config["end_position"]["y"], config["end_position"]["z"] };
    cam.start_time = { config["time_of_day"]["hour"], config["time_of_day"]["minute"], config["time_of_day"]["second"] };
    cam.text = config["text"];
    cam.cam = -1;
    cam.finish_cam = -1;
    return cam;
}

std::map<int, script_camera> load_cameras(nlohmann::json cameras_config)
{
    std::map<int, script_camera> ordered_cameras;

    for (nlohmann::json camera_config : cameras_config["cameras"])
    {
        int order = camera_config["order"];
        script_camera cam = create_camera_from_config(camera_config);
        ordered_cameras[order] = cam;
    }

    return ordered_cameras;
}

script_cinematic_config camera_util::get_cinematics_config(const std::string& cinematic_name) {
    std::ifstream config_file("jtmcraft_cinematics.json");
    if (!config_file) {
        logger::log_info("Could not open cinematic config file.");
        return {};
    }
    nlohmann::json config;
    config_file >> config;

    script_cinematic_config cinematic_config;
    cinematic cinematic_to_play;

    cinematic_to_play.music_event = config[cinematic_name]["music"];

    std::map<int, script_camera> ordered_cameras = load_cameras(config[cinematic_name]);

    for (const auto& pair : ordered_cameras) {
        cinematic_to_play.cameras[pair.first - 1] = pair.second;
    }
    cinematic_config.cinematics[cinematic_name] = cinematic_to_play;
    
    return cinematic_config;
}

void camera_util::play_cinematic(const std::string& cinematic_name) {
    constexpr int fade_time = 2500;
    script_cinematic_config cinematic_config = get_cinematics_config(cinematic_name);

    if (cinematic_config.cinematics.empty()) {
        logger::log_info("No cinematic by that name to play.");
        return;
    }
    
    cinematic cinematic_to_play = cinematic_config.cinematics[cinematic_name];
    const Player player = PLAYER::PLAYER_ID();
    PLAYER::SET_PLAYER_CONTROL(player, false, 0, false);

    
    fade_out(fade_time);
    const int this_hour = TIME::GET_CLOCK_HOURS();
    const int this_minute = TIME::GET_CLOCK_MINUTES();
    const int this_second = TIME::GET_CLOCK_SECONDS();

    for (size_t id = 0; id < cinematic_to_play.cameras.size(); ++id) {
        auto& camera = cinematic_to_play.cameras[static_cast<int>(id)];

        TIME::SET_CLOCK_TIME(camera.start_time.hour, camera.start_time.minute, camera.start_time.second);
        
        camera.cam = CAM::CREATE_CAM(const_cast<char*>("DEFAULT_SCRIPTED_CAMERA"), false);
        CAM::SET_CAM_COORD(camera.cam, camera.start_position.x, camera.start_position.y, camera.start_position.z);

        camera.finish_cam = CAM::CREATE_CAM(const_cast<char*>("DEFAULT_SCRIPTED_CAMERA"), false);
        CAM::SET_CAM_COORD(camera.finish_cam, camera.end_position.x, camera.end_position.y, camera.end_position.z);
    }

    CAM::_0x69D65E89FFD72313(true, true);
    AUDIO::PREPARE_MUSIC_EVENT(const_cast<char*>(cinematic_to_play.music_event.c_str()));
    AUDIO::TRIGGER_MUSIC_EVENT(const_cast<char*>(cinematic_to_play.music_event.c_str()));

    for (size_t id = 0; id < cinematic_to_play.cameras.size(); ++id) {
        const int index = static_cast<int>(id);
        const Vector3 position = cinematic_to_play.cameras[index].start_position;
        STREAMING::_SET_FOCUS_AREA(position.x, position.y, position.z, 0.0f, 0.0f, 0.0f);
        
        while (!STREAMING::_0xDA8B2EAF29E872E2(position.x, position.y, position.z)) {
            WAIT(5);
        }
        CAM::SET_CAM_ACTIVE(cinematic_to_play.cameras[index].cam, true);

        fade_in(fade_time);
        
        if (!cinematic_to_play.cameras[index].rotate_instead_of_point) {
            CAM::SET_CAM_ACTIVE_WITH_INTERP(cinematic_to_play.cameras[index].finish_cam, cinematic_to_play.cameras[index].cam, 22500, 3, 3);
            const Vector3 point_at = cinematic_to_play.cameras[index].point_cam_at;
            CAM::POINT_CAM_AT_COORD(cinematic_to_play.cameras[index].finish_cam, point_at.x, point_at.y, point_at.z);
        } else {
            CAM::SET_CAM_ROT(cinematic_to_play.cameras[index].finish_cam, 0.0f, 0.0f, cinematic_to_play.cameras[index].point_cam_at.z, 0);
            CAM::SET_CAM_ACTIVE_WITH_INTERP(cinematic_to_play.cameras[index].finish_cam, cinematic_to_play.cameras[index].cam, 22500, 3, 3);
        }

        CAM::RENDER_SCRIPT_CAMS(true, true, 0, false, false, false);
        graphics_util::wait_and_draw_center_text(22500, cinematic_to_play.cameras[index].text, ui_color::red_opaque);

        WAIT(1000);
        fade_out(fade_time);
    }

    CAM::RENDER_SCRIPT_CAMS(false, true, 0, false, false, false);
    AUDIO::TRIGGER_MUSIC_EVENT(const_cast<char*>("MC_MUSIC_STOP"));
    CAM::_0x69D65E89FFD72313(false, false);

    for (size_t id = 0; id < cinematic_to_play.cameras.size(); ++id) {
        const int index = static_cast<int>(id);
        CAM::DESTROY_CAM(cinematic_to_play.cameras[index].cam, false);
        CAM::DESTROY_CAM(cinematic_to_play.cameras[index].finish_cam, false);
    }

    STREAMING::CLEAR_FOCUS();

    const Vector3 player_position = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true, true);
    while (!STREAMING::_0xDA8B2EAF29E872E2(player_position.x, player_position.y, player_position.z)) {
        WAIT(5);
    }

    TIME::SET_CLOCK_TIME(this_hour, this_minute, this_second);
    fade_in(fade_time);
    PLAYER::SET_PLAYER_CONTROL(player, true, 0, false);
}

Vector3 camera_util::pointing_at(const Vector3& position, const float distance) {
    const Vector3 camera_rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);
    const Vector3 direction = math_util::rotation_to_direction_unit_vector(camera_rotation);
    
    return {
        position.x + direction.x * distance,
        position.y + direction.y * distance,
        position.z + direction.z * distance
    };
}

bool camera_util::ray_cast(const float distance, Entity* entity_hit) {
    BOOL ray_hit_an_entity;
    Vector3 end_coords;
    Vector3 surface_normal;
    const Vector3 camera_coords = CAM::GET_GAMEPLAY_CAM_COORD();
    const Vector3 distant_coords = pointing_at(camera_coords, distance);

    const int ray = SHAPETEST::_START_SHAPE_TEST_RAY(camera_coords.x, camera_coords.y, camera_coords.z, distant_coords.x, distant_coords.y, distant_coords.z, -1, 0, 7);
    SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &ray_hit_an_entity, &end_coords, &surface_normal, entity_hit);

    return static_cast<bool>(ray_hit_an_entity);
}

bool camera_util::get_entity_free_aiming_at(Entity* entity) {
    const Player player = PLAYER::PLAYER_ID();

    if (PLAYER::IS_PLAYER_FREE_AIMING(player)) {
        return PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), entity);    
    }
    
    return false;
}

void camera_util::fade_in(const int fade_time) {
    if (CAM::IS_SCREEN_FADED_OUT()) {
        CAM::DO_SCREEN_FADE_IN(fade_time);
        while (!CAM::IS_SCREEN_FADED_IN()) {
            WAIT(1);
        }
    }
}

void camera_util::fade_out(int fade_time) {
    if (CAM::IS_SCREEN_FADED_IN()) {
        CAM::DO_SCREEN_FADE_OUT(fade_time);
        while (!CAM::IS_SCREEN_FADED_OUT()) {
            WAIT(1);
        }
    }
}


