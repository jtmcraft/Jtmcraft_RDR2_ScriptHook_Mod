#include "entity.h"

#include <iostream>
#include <string>
#include <vector>

#include "../../../inc/natives.h"

int entity_util::get_last_damage_bone(const Ped ped) {
    int bone;
    
    PED::GET_PED_LAST_DAMAGE_BONE(ped, &bone);
    
    return bone;
}

Ped entity_util::get_player_horse() {
    const Ped player_ped = PLAYER::PLAYER_PED_ID();
    Any horse_ped;
    
    if (PED::IS_PED_ON_MOUNT(player_ped)) {
        horse_ped = PED::GET_MOUNT(player_ped);
    } else {
        horse_ped = PLAYER::_0xF49F14462F0AE27C(PLAYER::PLAYER_ID());
    }

    return static_cast<Ped>(horse_ped);
}

void entity_util::player_horse_female() {
    const Ped horse_ped = get_player_horse();
    PED::_0x5653AB26C82938CF(horse_ped, 0xA28B, 1.0f);
    PED::_0xCC8CA3E88256E58F(horse_ped, false, true, true, true, false);
}

void entity_util::player_horse_max_stats() {
    const Ped horse_ped = get_player_horse();
    static std::vector<int> attribute_indexes = {0, 1, 7};
	
    for (const int attribute_index : attribute_indexes) {
        const Any max = ATTRIBUTE::_0x704674A0535A471D(horse_ped, attribute_index);
        ATTRIBUTE::_0x09A59688C26D88DF(horse_ped, attribute_index, 0);
        ATTRIBUTE::_0x75415EE0CB583760(horse_ped, attribute_index, 0);
        ATTRIBUTE::_0x5DA12E025D47D4E5(horse_ped, attribute_index, max);
        ATTRIBUTE::_0x920F9488BD115EFB(horse_ped, attribute_index, 0);
        if (attribute_index == 7) {
            PED::_0xA69899995997A63B(horse_ped, max);
        }        
    }
}
