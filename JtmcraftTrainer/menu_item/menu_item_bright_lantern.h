#pragma once

#include "../scriptmenu.h"
#include "../data/configuration.h"
#include "../util/inventory.h"

class menu_item_bright_lantern final : public MenuItemSwitchable
{
    void OnSelect() override {
        const bool new_state = !GetState();
        SetState(new_state);
    }

    void OnFrame() override {
        if (player_inventory::is_wielding_lantern()) {
            const float high_intensity = configuration::get_instance().get_or_else<float>("jtmcraft:player_lantern.intensity.high", 1000.0f);
            const float default_intensity = configuration::get_instance().get_or_else<float>("jtmcraft:player_lantern.intensity.default", 100.0f);
            player_inventory::set_lantern_intensity(GetState() ? high_intensity : default_intensity);
        }
    }

public:
    explicit menu_item_bright_lantern(const string& caption) : MenuItemSwitchable(caption) {}
};
