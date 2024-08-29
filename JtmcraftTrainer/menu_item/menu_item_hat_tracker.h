#pragma once
#include "../scriptmenu.h"
#include "../util/radar.h"
#include "../util/util.h"

class menu_item_hat_tracker final : public MenuItemSwitchable
{
    Blip hat_blip_;
    int data_[100] = {0};
    int hat_knocked_off_data_size_;
    Hash hat_knocked_off_hash_;
    int hat_equipped_data_size_;
    Hash hat_equipped_hash_;

    void OnSelect() override {
        const bool new_state = !GetState();
        SetState(new_state);
    }

    void OnFrame() override {
        if (!GetState()) {
            radar_util::remove_blip(hat_blip_);
            return;
        }

        const int number_of_events = SCRIPT::GET_NUMBER_OF_EVENTS(0);

        for (int i = 0; i < number_of_events; ++i) {
            const Hash event_hash = SCRIPT::GET_EVENT_AT_INDEX(0, i);
            const bool is_hat_equipped = event_hash == hat_equipped_hash_;
            const bool is_hat_knocked_off = event_hash == hat_knocked_off_hash_;

            if (is_hat_equipped || is_hat_knocked_off) {
                if (is_hat_equipped) {
                    SCRIPT::GET_EVENT_DATA(0, i, data_, hat_equipped_data_size_);
                    radar_util::remove_blip(hat_blip_);
                }
                else if (is_hat_knocked_off) {
                    radar_util::remove_blip(hat_blip_);
                    SCRIPT::GET_EVENT_DATA(0, i, data_, hat_knocked_off_data_size_);
                    const Ped player_ped = data_[0];
                    const Vector3 player_coords = ENTITY::GET_ENTITY_COORDS(player_ped, true, true);
                    hat_blip_ = radar_util::add_blip_at_coords(util::get_hash("BLIP_HAT"), 0.2f, "Your hat", player_coords);
                }

                return;
            }
        }
    }

public:
    explicit menu_item_hat_tracker(const string& caption) : MenuItemSwitchable(caption) {
        hat_blip_ = 0;
        hat_knocked_off_data_size_ = 5;
        hat_knocked_off_hash_ = util::get_hash("EVENT_PLAYER_HAT_KNOCKED_OFF");
        hat_equipped_data_size_ = 10;
        hat_equipped_hash_ = util::get_hash("EVENT_PLAYER_HAT_EQUIPPED");
        OnSelect();
    }
};
