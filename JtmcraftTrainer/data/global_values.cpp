#include "global_values.h"

int global_values::get_headshots() const {
    return headshots_;
}

void global_values::increment_headshots() {
    ++headshots_;
}

void global_values::set_headshots(const int headshots) {
    headshots_ = headshots;
}

float global_values::get_screen_width() const {
    return screen_width_;
}

float global_values::get_screen_height() const {
    return screen_height_;
}

