#pragma once

#include "../scriptmenu.h"
#include "../scripts/debug_screen.h"
#include "../util/graphics.h"

class menu_item_debug_screen final : public MenuItemSwitchable
{
    void OnSelect() override {
        const bool new_state = !GetState();
        SetState(new_state);
    }

    void OnFrame() override {
        if (GetState()) {
            const bool show_position_vector = configuration::get_instance().get_or_else("jtmcraft:show_location.show_position_vector", true);
            const bool show_camera_pointing_at = configuration::get_instance().get_or_else("jtmcraft:show_location.show_camera_pointing_at", true);
            debug_screen::show_background(show_position_vector, show_camera_pointing_at);;
            debug_screen::show_player_position(show_position_vector, show_camera_pointing_at);


        }
    }

public:
    explicit menu_item_debug_screen(const string& caption) : MenuItemSwitchable(caption) {
        if (configuration::get_instance().get_or_else("jtmcraft:show_location.start_with_on", false)) {
            OnSelect();
        }
    }
};
