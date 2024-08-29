#pragma once
#include <string>

#include "timed_script.h"
#include "../util/timer.h"

class headshot_tracker final : public timed_script
{
    real_timer timer_;
    int last_headshot_count_ = 0;
    int longest_distance_reward_amount_ = 1500;
    const int rampage_interval_ = 5000;
    int rampage_threshold_ = 4;
    std::string rampage_reward_name_ = "PROVISION_GOLD_NUGGET";
    int rampage_reward_amount_ = 1;

    void reset_headshots();
    void handle_rampage_interval_exceeded();
    void handle_rampage_threshold_reached();
    
public:
    headshot_tracker();

    void do_update() override;
};
