#include "false_accusation.h"

#include <iostream>
#include <sstream>
#include <string>

#include "../../../inc/natives.h"
#include "../data/configuration.h"
#include "../util/crime.h"
#include "../util/logger.h"
#include "../util/toast.h"

void false_accusations::do_update() {
    if (should_falsely_accuse_player()) {
        falsely_accuse_player();
        accused_ = true;
    }

    update_count_value();

    if (is_max_updates_exceeded()) {
        reset_values();
    }
}

void false_accusations::falsely_accuse_player() {
    const Hash crime_hash = crime::random_crime();
    notify_player_of_false_accusation(crime_hash);
    const Any bounty = PURSUIT::_0x35E5E21F9159849C(crime_hash);
    PURSUIT::_0xF60386770878A98F(PLAYER::PLAYER_ID(), crime_hash, bounty, 0, true);
}

void false_accusations::notify_player_of_false_accusation(const Hash& crime) {
    const std::string crime_name = crime::crime_name(crime);
    std::stringstream stream;
    stream << "You've been falsely accused of ~COLOR_OBJECTIVE~" << crime_name << "~s~";
    toast::objective(stream.str());
}

false_accusations::false_accusations() : timed_script(3600), accused_(false) {
    configuration& config = configuration::get_instance();
    initial_value_ = config.get_or_else<float>("jtmcraft:false_accusations.initial_value", 0.005f);
    rate_ = config.get_or_else<float>("jtmcraft:false_accusations.rate", 0.2f);
    coefficient_ = config.get_or_else<float>("jtmcraft:false_accusations.coefficient", 7.5f);
    update_count_ = 0;
}

float false_accusations::calculate_chance() const {
    const float initial_value = configuration::get_instance().get_or_else<float>("jtmcraft:false_accusations.initial_value", initial_value_);
    const float rate = configuration::get_instance().get_or_else<float>("jtmcraft:false_accusations.rate", rate_);
    const float coefficient = configuration::get_instance().get_or_else<float>("jtmcraft:false_accusations.coefficient", coefficient_);
    
    const float accusation_intensity = initial_value * std::pow(1.0f + rate, static_cast<float>(update_count_));
    return accusation_intensity * coefficient;
}

bool false_accusations::should_falsely_accuse_player() const {
    const float roll = GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0.0f, 1.0f);
    const float chance = calculate_chance();
    std::stringstream stream;
    stream << "false accusation; roll: " << std::to_string(roll) << "; chance: " << std::to_string(chance);
    logger::log_info(stream.str());
    const bool should_accuse = !accused_ && roll <= chance;
    
    return should_accuse;
}

void false_accusations::update_count_value() {
    ++update_count_;
}

bool false_accusations::is_max_updates_exceeded() const {
    return update_count_ > 23;
}

void false_accusations::reset_values() {
    update_count_ = 0;
    accused_ = false;
}
