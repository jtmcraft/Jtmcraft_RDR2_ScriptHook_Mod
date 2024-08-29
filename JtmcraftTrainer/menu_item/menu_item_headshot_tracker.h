#pragma once

#include "../scriptmenu.h"
#include "../data/global_values.h"
#include "../scripts/headshot_tracker.h"
#include "../util/entity.h"
#include "../util/util.h"

class menu_item_headshot_tracker final : public MenuItemSwitchable
{
    int entity_damaged_data_[100] = {0};
    int entity_damaged_data_size_ = 9;
    Hash entity_damaged_event_hash_;
    headshot_tracker headshot_tracker_;

    void OnSelect() override {
        const bool new_state = !GetState();
        SetState(new_state);
    }

    void handle_entity_damaged_event(const int event_index) {
        SCRIPT::GET_EVENT_DATA(0, event_index, entity_damaged_data_, entity_damaged_data_size_);
        const int damage_cause = entity_damaged_data_[2];
        const int victim = entity_damaged_data_[0];
        if (damage_cause == PLAYER::PLAYER_PED_ID() && ENTITY::IS_ENTITY_DEAD(victim) && entity_util::get_last_damage_bone(victim) == 21030) {
            global_values::get_instance().increment_headshots();
        }
    }

    void OnFrame() override {
        if (!GetState()) {
            return;
        }
        const int number_of_events = SCRIPT::GET_NUMBER_OF_EVENTS(0);
        for (int event_index = 0; event_index < number_of_events; ++event_index) {
            const Hash event_hash = SCRIPT::GET_EVENT_AT_INDEX(0, event_index);
            const bool is_entity_damage_event = event_hash == entity_damaged_event_hash_;
            if (is_entity_damage_event) {
                handle_entity_damaged_event(event_index);
            }
        }

        headshot_tracker_.do_update();
    }

public:
    explicit menu_item_headshot_tracker(const string& caption) : MenuItemSwitchable(caption) {
        entity_damaged_event_hash_ = util::get_hash("EVENT_ENTITY_DAMAGED");
        OnSelect();
    }
};
