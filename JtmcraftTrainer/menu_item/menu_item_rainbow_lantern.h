#pragma once

#include "../scriptmenu.h"
#include "../data/configuration.h"
#include "../scripts/rainbow_lantern.h"
#include "../util/inventory.h"
#include "../util/timer.h"

class menu_item_rainbow_lantern final : public MenuItemSwitchable
{
    rainbow_lantern lantern_{
        configuration::get_instance().get_or_else("jtmcraft:player_lantern.rainbow.delay_ms", 100)
    };
    real_timer timer_;

    void OnSelect() override {
        const bool new_state = !GetState();
        SetState(new_state);
    }

    void OnFrame() override {
        if (player_inventory::is_wielding_lantern()) {
            if (GetState()) {
                lantern_.set_interval(configuration::get_instance().get_or_else("jtmcraft:player_lantern.rainbow.delay_ms", 100));

                if (timer_.elapsed_time() >= 1) {
                    lantern_.on_update();
                    lantern_.on_reset();
                    timer_.restart();
                }
            }
            else {
                const int red = configuration::get_instance().get_or_else<int>("jtmcraft:player_lantern.color.red", 255);
                const int green = configuration::get_instance().get_or_else<int>("jtmcraft:player_lantern.color.green", 255);
                const int blue = configuration::get_instance().get_or_else<int>("jtmcraft:player_lantern.color.blue", 255);
                player_inventory::set_lantern_light_color(red, green, blue);
            }
        }
    }

public:
    explicit menu_item_rainbow_lantern(const string& caption) : MenuItemSwitchable(caption) {}
};
