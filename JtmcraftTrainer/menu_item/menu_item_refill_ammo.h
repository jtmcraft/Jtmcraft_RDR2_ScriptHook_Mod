#pragma once

#include "../scriptmenu.h"
#include "../data/configuration.h"
#include "../util/util.h"

const vector<string> default_ammo_types = {
    "AMMO_22",
    "AMMO_ARROW",
    "AMMO_ARROW_DYNAMITE",
    "AMMO_ARROW_FIRE",
    "AMMO_ARROW_IMPROVED",
    "AMMO_ARROW_POISON",
    "AMMO_ARROW_SMALL_GAME",
    "AMMO_DYNAMITE",
    "AMMO_MOLOTOV",
    "AMMO_PISTOL",
    "AMMO_PISTOL_EXPRESS",
    "AMMO_PISTOL_EXPRESS_EXPLOSIVE",
    "AMMO_PISTOL_HIGH_VELOCITY",
    "AMMO_PISTOL_SPLIT_POINT",
    "AMMO_REPEATER",
    "AMMO_REPEATER_EXPRESS",
    "AMMO_REPEATER_EXPRESS_EXPLOSIVE",
    "AMMO_REPEATER_HIGH_VELOCITY",
    "AMMO_REPEATER_SPLIT_POINT",
    "AMMO_REVOLVER",
    "AMMO_REVOLVER_EXPRESS",
    "AMMO_REVOLVER_EXPRESS_EXPLOSIVE",
    "AMMO_REVOLVER_HIGH_VELOCITY",
    "AMMO_REVOLVER_SPLIT_POINT",
    "AMMO_RIFLE",
    "AMMO_RIFLE_ELEPHANT",
    "AMMO_RIFLE_EXPRESS",
    "AMMO_RIFLE_EXPRESS_EXPLOSIVE",
    "AMMO_RIFLE_HIGH_VELOCITY",
    "AMMO_RIFLE_SPLIT_POINT",
    "AMMO_SHOTGUN",
    "AMMO_SHOTGUN_BUCKSHOT_INCENDIARY",
    "AMMO_SHOTGUN_SLUG",
    "AMMO_SHOTGUN_SLUG_EXPLOSIVE",
    "AMMO_THROWING_KNIVES",
    "AMMO_TOMAHAWK"
};

class menu_item_refill_ammo final : public MenuItemDefault
{
    vector<string> refillable_ammo_types_;

    void OnSelect() override {
        const Ped player_ped = PLAYER::PLAYER_PED_ID();
        const int amount = configuration::get_instance().get_or_else<int>("jtmcraft:cheats.ammo.refill_amount", 500);
        const vector<string> ammo_types = configuration::get_instance().get_or_else<vector<string>>("jtmcraft:cheats.ammo.refillable_types", refillable_ammo_types_);
        for (const auto& ammo_type : ammo_types) {
            WEAPON::SET_PED_AMMO_BY_TYPE(player_ped, util::get_hash(ammo_type), amount);
        }
        SetStatusText("Ammo refilled.");
    }

public:
    explicit menu_item_refill_ammo(const string& caption) : MenuItemDefault(caption) {
        refillable_ammo_types_ = configuration::get_instance().get_or_else<vector<string>>("jtmcraft:cheats.ammo.refillable_types", default_ammo_types);
    }
};
