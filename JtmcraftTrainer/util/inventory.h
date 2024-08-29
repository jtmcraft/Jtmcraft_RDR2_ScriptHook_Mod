#pragma once

#include "../../../inc/types.h"

struct inventory_guid
{
    alignas(8) int data1;
    alignas(8) int data2;
    alignas(8) int data3;
    alignas(8) int data4;
};

struct inventory_slot_info
{
    alignas(8) inventory_guid guid;
    alignas(8) int f_1;
    alignas(8) int f_2;
    alignas(8) int f_3;
    alignas(8) Hash slot_id;
};

struct inventory_item_info
{
    alignas(8) int f_0;
    alignas(8) int f_1;
    alignas(8) int group;
    alignas(8) int f_3;
    alignas(8) int f_4;
    alignas(8) int f_5;
    alignas(8) int f_6;
};

enum : Hash
{
    item_group_clothing = 0xC2286F01,
    item_group_horse = 0x95A6F147,
    item_group_upgrade = 0x80FB92C
};

namespace player_inventory {
    bool give_item(Hash item, int amount);
    Entity get_weapon_entity();
    bool is_wielding_lantern();
    void set_lantern_intensity(float intensity);
    void set_lantern_light_color(int red, int green, int blue);
}
