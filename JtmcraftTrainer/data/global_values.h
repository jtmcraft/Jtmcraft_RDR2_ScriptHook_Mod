#pragma once
#include "../../inc/types.h"

class global_values
{
    global_values() = default;
    ~global_values() = default;
    
    int headshots_ = 0;
    float screen_width_ = static_cast<float>(GetSystemMetrics(SM_CXSCREEN));
    float screen_height_ = static_cast<float>(GetSystemMetrics(SM_CYSCREEN));

public:
    static const Hash default_add_reason;

    global_values(global_values const&) = delete;
    global_values& operator=(global_values const&) = delete;
    
    static global_values& get_instance() {
        static global_values instance;
        return instance;
    }

    [[nodiscard]] int get_headshots() const;
    void increment_headshots();
    void set_headshots(int headshots);
    [[nodiscard]] float get_screen_width() const;
    [[nodiscard]] float get_screen_height() const;
};
