#include "inventory.h"

#include "graphics.h"
#include "../../inc/natives.h"

namespace player_inventory {
    inventory_guid create_new_guid() {
        inventory_guid guid{};
        return guid;
    }

    inventory_guid get_item_guid(const Hash item, inventory_guid guid, const Hash slotId) {
        inventory_guid out_guid{};
        ITEMS::_0x886DFD3E185C8A89(1, reinterpret_cast<Any*>(&guid), item, slotId, reinterpret_cast<Any*>(&out_guid));
        return out_guid;
    }

    inventory_guid get_guid() {
        return get_item_guid(GAMEPLAY::GET_HASH_KEY("CHARACTER"), create_new_guid(), GAMEPLAY::GET_HASH_KEY("SLOTID_NONE"));
    }

    Hash get_item_group(const Hash item) {
        inventory_item_info info{};

        if (!ITEMDATABASE::_0x6D5D51B188333FD1(item, 0)) {
            return 0;
        }

        if (!ITEMDATABASE::_0xFE90ABBCBFDC13B2(item, reinterpret_cast<Any*>(&info))) {
            return 0;
        }

        return info.group;
    }

    inventory_slot_info get_item_slot_info(const Hash item) {
        inventory_slot_info slot_info{};

        const Hash satchel_hash = GAMEPLAY::GET_HASH_KEY("SLOTID_SATCHEL");
        const Hash wardrobe_slot_hash = GAMEPLAY::GET_HASH_KEY("SLOTID_WARDROBE");
        const Hash active_horse_slot_hash = GAMEPLAY::GET_HASH_KEY("SLOTID_ACTIVE_HORSE");
        const Hash upgrade_slot_hash = GAMEPLAY::GET_HASH_KEY("SLOTID_UPGRADE");
        const Hash wardrobe_hash = GAMEPLAY::GET_HASH_KEY("WARDROBE");
        const Hash character_hash = GAMEPLAY::GET_HASH_KEY("CHARACTER");

        slot_info.guid = get_guid();
        slot_info.slot_id = satchel_hash;

        switch (get_item_group(item)) {
        case item_group_clothing:
            if (!ITEMS::_0x780C5B9AE2819807(item, wardrobe_slot_hash)) {
                slot_info.guid = get_item_guid(wardrobe_hash, slot_info.guid, wardrobe_slot_hash);
                slot_info.slot_id = ITEMS::_0x6452B1D357D81742(item, wardrobe_hash);
            }
            else {
                slot_info.slot_id = wardrobe_slot_hash;
            }
            break;

        case item_group_horse:
            slot_info.slot_id = active_horse_slot_hash;
            break;

        case item_group_upgrade:
            if (ITEMS::_0x780C5B9AE2819807(item, upgrade_slot_hash)) {
                slot_info.slot_id = upgrade_slot_hash;
            }
            break;

        default:
            if (ITEMS::_0x780C5B9AE2819807(item, satchel_hash)) {
                slot_info.slot_id = satchel_hash;
            }
            else if (ITEMS::_0x780C5B9AE2819807(item, wardrobe_slot_hash)) {
                slot_info.slot_id = wardrobe_slot_hash;
            }
            else {
                slot_info.slot_id = ITEMS::_0x6452B1D357D81742(item, character_hash);
            }
            break;
        }

        return slot_info;
    }

    bool add_item_with_guid(const Hash item, inventory_guid& guid, inventory_slot_info& slot_info, const int quantity,
                                const Hash add_reason) {
        if (!ITEMS::_0xB881CA836CC4B6D4(reinterpret_cast<Any*>(&slot_info.guid))) {
            return false;
        }

        if (!ITEMS::_0xCB5D11F9508A928D(1, reinterpret_cast<Any*>(&guid), reinterpret_cast<Any*>(&slot_info.guid), item,
                                        slot_info.slot_id, quantity, add_reason)) {
            return false;
        }

        return true;
    }

    bool give_item(const Hash item, const int amount) {
        inventory_slot_info slot_info = get_item_slot_info(item);
        inventory_guid guid = get_item_guid(item, slot_info.guid, slot_info.slot_id);
        return add_item_with_guid(item, guid, slot_info, amount, GAMEPLAY::GET_HASH_KEY("ADD_REASON_DEFAULT"));
    }

    Entity get_weapon_entity() {
        const Entity weapon_entity = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID(), 0);
        return weapon_entity;
    }
    
    bool is_wielding_lantern() {
        const Ped player_ped = PLAYER::PLAYER_PED_ID();
        Hash weapon_hash;
        const Hash davy_lantern = GAMEPLAY::GET_HASH_KEY("WEAPON_MELEE_LANTERN");
        const Hash lantern = GAMEPLAY::GET_HASH_KEY("WEAPON_MELEE_DAVY_LANTERN");
        WEAPON::GET_CURRENT_PED_WEAPON(player_ped, &weapon_hash, true, 0, true);
        return weapon_hash == lantern || weapon_hash == davy_lantern;
    }

    void set_lantern_intensity(const float intensity) {
        if (is_wielding_lantern()) {
            const Entity lantern = get_weapon_entity();
            graphics_util::set_entity_light_intensity(lantern, intensity);
        }
    }

    void set_lantern_light_color(const int red, const int green, const int blue) {
        if (is_wielding_lantern()) {
            const Entity lantern = get_weapon_entity();
            graphics_util::set_entity_light_color(lantern, red, green, blue);
        }
    }
}
