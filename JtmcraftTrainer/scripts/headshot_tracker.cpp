#include "headshot_tracker.h"

#include "../data/configuration.h"
#include "../data/global_values.h"
#include "../util/inventory.h"
#include "../util/toast.h"
#include "../util/util.h"

headshot_tracker::headshot_tracker() : timed_script(0) {}

void headshot_tracker::reset_headshots() {
    global_values::get_instance().set_headshots(0);
    last_headshot_count_ = 0;
    timer_.restart();
}

void headshot_tracker::handle_rampage_interval_exceeded() {
    reset_headshots();
}

void headshot_tracker::handle_rampage_threshold_reached() {
    toast::rampage();
    player_inventory::give_item(util::get_hash(rampage_reward_name_), rampage_reward_amount_);
    reset_headshots();
}

void headshot_tracker::do_update() {
    const int rampage_interval = configuration::get_instance().get_or_else<int>("jtmcraft:rampage.interval_ms", rampage_interval_);
    const int rampage_threshold = configuration::get_instance().get_or_else<int>("jtmcraft:rampage.threshold", rampage_threshold_);
    
    if (timer_.elapsed_time() >= rampage_interval) {
        handle_rampage_interval_exceeded();
    } else if (global_values::get_instance().get_headshots() == rampage_threshold) {
        handle_rampage_threshold_reached();
    } else if (global_values::get_instance().get_headshots() > last_headshot_count_) {
        last_headshot_count_ = global_values::get_instance().get_headshots();
        timer_.restart();
    }
}
