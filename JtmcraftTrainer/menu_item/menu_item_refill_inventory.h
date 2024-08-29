#pragma once

#include "../scriptmenu.h"
#include "../util/inventory.h"
#include "../util/util.h"

const vector<string> default_inventory_items = {
    "CONSUMABLE_CHEESE_WEDGE",
    "CONSUMABLE_BAKED_BEANS_CAN",
    "CONSUMABLE_CARROT",
    "CONSUMABLE_BIG_GAME_MEAT_THYME_COOKED",
    "CONSUMABLE_BIG_GAME_MEAT_OREGANO_COOKED",
    "CONSUMABLE_BIG_GAME_MEAT_WILD_MINT_COOKED",
    "CONSUMABLE_SPECIAL_MEDICINE_CRAFTED",
    "CONSUMABLE_SPECIAL_SNAKE_OIL_CRAFTED",
    "CONSUMABLE_HORSE_REVIVER"
};

class menu_item_refill_inventory final : public MenuItemDefault
{
    vector<string> provisions_;
    
    void OnSelect() override {
        const int amount = configuration::get_instance().get_or_else<int>("jtmcraft:cheats.provisions.amount", 99);
        
        for (const auto& inventory_item : default_inventory_items) {
            player_inventory::give_item(util::get_hash(inventory_item), amount);
        }
        SetStatusText("Provisions refilled.");
    }

public:
    explicit menu_item_refill_inventory(const string& caption) : MenuItemDefault(caption) {}
};
