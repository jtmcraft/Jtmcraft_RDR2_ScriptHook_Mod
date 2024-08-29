#pragma once
#include "../scriptmenu.h"
#include "../scripts/false_accusation.h"
#include "../util/crime.h"
#include "../util/timer.h"

class menu_item_false_accusations final : public MenuItemSwitchable
{
    game_timer timer_;
    false_accusations false_accusations_;

    void OnSelect() override {
        const bool new_state = !GetState();
        SetState(new_state);
    }

    void update_or_reset() {
        if (timer_.has_game_second_passed()) {
            false_accusations_.on_update();
        } else {
            false_accusations_.on_reset();
        }
    }

    void OnFrame() override {
        const int current_bounty = crime::current_bounty_on_player();
        const int max_bounty = configuration::get_instance().get_or_else<int>("jtmcraft:false_accusations.max_bounty_pennies", 50000);
        
        if (UI::IS_PAUSE_MENU_ACTIVE() || !PLAYER::IS_PLAYER_CONTROL_ON(PLAYER::PLAYER_ID()) || !GetState() || current_bounty >= max_bounty) {
            return;
        }
        
        update_or_reset();            
        timer_.update_last_game_second();
    }
    
public:
    explicit menu_item_false_accusations(const std::string& caption) : MenuItemSwitchable(caption) {}
};
