#include "rainbow_lantern.h"

#include "../data/configuration.h"
#include "../util/inventory.h"
#include "../util/rgb.h"

rainbow_lantern::rainbow_lantern(const int interval) : timed_script(interval), counter_(0) {}

void rainbow_lantern::do_update() {
    int red;
    int green;
    int blue;
    constexpr float full_cycle = 255.0f;
    constexpr float degrees_in_circle = 360.0f;
    const float saturation = configuration::get_instance().get_or_else<float>("jtmcraft:player_lantern.rainbow.saturation", 0.9f);
    const float brightness = configuration::get_instance().get_or_else<float>("jtmcraft:player_lantern.rainbow.brightness", 0.1f);
    const float color_number = (static_cast<float>(counter_) > full_cycle) ? (static_cast<float>(counter_) - full_cycle) : static_cast<float>(counter_);
    const float hue = (color_number / full_cycle) * degrees_in_circle;
    rgb_util::from_hsb(hue, saturation, brightness, &red, &green, &blue);
    counter_ = (counter_ + 1) % static_cast<int>(full_cycle * 2);
    player_inventory::set_lantern_light_color(red, green, blue);
}
