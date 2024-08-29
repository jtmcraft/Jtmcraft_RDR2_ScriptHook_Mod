#pragma once

#include <chrono>

class real_timer
{
    using Clock = std::chrono::steady_clock;
    std::chrono::time_point<Clock> start_time_{Clock::now()};
    
public:
    real_timer();
    void restart();
    long long elapsed_time() const;
};

class game_timer
{
public:
    int last_game_second_;

    game_timer();
    void update_last_game_second();
    bool has_game_second_passed() const;
};
