#pragma once
#include "../scriptmenu.h"
#include "../util/camera_util.h"

class menu_item_cinematic_test final : public MenuItemDefault
{
    bool cinematic_running_;

    void OnSelect() override {
        if (!cinematic_running_) {

            
            const Player player = PLAYER::PLAYER_ID();
            const bool original_invincible = PLAYER::GET_PLAYER_INVINCIBLE(player);
            PLAYER::SET_PLAYER_INVINCIBLE(player, true);
            
            cinematic_running_ = true;
            camera_util::play_cinematic("intro_cinematic");
            cinematic_running_ = false;

            
            
            PLAYER::SET_PLAYER_INVINCIBLE(player, original_invincible);
        }
    }
    
public:
    explicit menu_item_cinematic_test(const std::string& caption) : MenuItemDefault(caption) {
        cinematic_running_ = false;
    }
};
