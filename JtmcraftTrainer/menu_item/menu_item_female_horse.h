#pragma once
#include "../scriptmenu.h"
#include "../util/entity.h"

class menu_item_female_horse final : public MenuItemDefault
{
    void OnSelect() override {
        entity_util::player_horse_female();
    }
    
public:
    explicit menu_item_female_horse(const std::string& caption) : MenuItemDefault(caption) {}
};
