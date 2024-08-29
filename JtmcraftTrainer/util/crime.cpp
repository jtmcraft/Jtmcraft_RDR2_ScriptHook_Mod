#include "crime.h"

#include "../../../inc/natives.h"

Hash crime::random_crime() {
    const int dim = static_cast<int>(crime_list.size()) - 1;
    return crime_list[GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, dim)];
}

std::string crime::crime_name(const Hash crime_hash) {
    const auto crime_name_iter = crime_names.find(crime_hash);
    if (crime_name_iter != crime_names.end()) {
        return crime_name_iter->second;
    }
    return "Unknown Crime";
}

int crime::current_bounty_on_player() {
    const Any price_on_player = PURSUIT::GET_PLAYER_PRICE_ON_A_HEAD(PLAYER::PLAYER_ID());
    return static_cast<int>(price_on_player);
}
