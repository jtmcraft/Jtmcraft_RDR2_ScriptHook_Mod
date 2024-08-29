#include "timed_script.h"

timed_script::timed_script(const int interval) : interval_(interval), units_(0), updated_(false) {}

bool timed_script::should_update() const {
    return units_ >= interval_ && !updated_;
}

void timed_script::on_update() {
    ++units_;
    
    if (should_update()) {
        do_update();
        units_ = 0;
        updated_ = true;
    }
}

void timed_script::on_reset() {
    updated_ = false;
}

int timed_script::get_interval() const {
    return interval_;
}

void timed_script::set_interval(int interval) {
    interval_ = interval;
}
