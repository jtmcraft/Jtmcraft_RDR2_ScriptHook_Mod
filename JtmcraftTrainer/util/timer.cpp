#include "timer.h"

#include "../../inc/natives.h"

real_timer::real_timer() {
    restart();
}

void real_timer::restart() {
    start_time_ = Clock::now();
}

long long real_timer::elapsed_time() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - start_time_).count();
}

game_timer::game_timer() {
    update_last_game_second();
}

void game_timer::update_last_game_second() {
    last_game_second_ = TIME::GET_CLOCK_SECONDS();
}

bool game_timer::has_game_second_passed() const {
    const int this_game_second = TIME::GET_CLOCK_SECONDS(); 
    return this_game_second != last_game_second_;
}
