#pragma once
#include "../scriptmenu.h"
#include "../util/entity.h"

class menu_item_max_horse_stats final : public MenuItemDefault
{
    void OnSelect() override {
        entity_util::player_horse_max_stats();
    }
    
public:
    explicit menu_item_max_horse_stats(const std::string& caption) : MenuItemDefault(caption) {}
};
