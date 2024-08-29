#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "../../../inc/types.h"

namespace crime {
    const std::vector<Hash> crime_list = {
        0x68134DC7,
        0x0BADC882,
        0x971EA5AF,
        0x55AD2BEB,
        0xE28ECE7E,
        0xA3BEDE4C,
        0xFC738E61,
        0x647D2A5A
    };

    const std::unordered_map<Hash, std::string> crime_names = {
        {0x68134DC7, "Arson"},
        {0x0BADC882, "Assault"},
        {0x971EA5AF, "Grave Robbery"},
        {0x55AD2BEB, "Looting"},
        {0xE28ECE7E, "Murder"},
        {0xA3BEDE4C, "Robbery"},
        {0xFC738E61, "Stagecoach Robbery"},
        {0x647D2A5A, "Train Robbery"}
    };
    
    Hash random_crime();
    std::string crime_name(Hash crime_hash);
    int current_bounty_on_player();
}
