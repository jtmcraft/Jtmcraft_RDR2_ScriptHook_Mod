#pragma once

#include "../scriptmenu.h"
#include "../util/entity.h"
#include "../util/graphics.h"
#include "../util/math.h"

class menu_item_night_light final : public MenuItemSwitchable
{
    void OnSelect() override {
        const bool new_state = !GetState();
        SetState(new_state);
    }

    void OnFrame() override {
        if (GetState()) {
            constexpr Vector3 offset_vector = {1.0f, 1.0f, 2.0f};
            const Vector3 night_light_coords = math::forward_vector(PLAYER::PLAYER_PED_ID(), offset_vector, false);

            graphics_util::draw_light(night_light_coords, ui_color::white_opaque, 20.0f, 10.0f);
        }
    }

public:
    explicit menu_item_night_light(const string& caption) : MenuItemSwitchable(caption) {}
};
