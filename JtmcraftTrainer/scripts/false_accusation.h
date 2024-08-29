#pragma once

#include "timed_script.h"
#include "../../../inc/types.h"

class false_accusations final : public timed_script
{
public:
    float calculate_chance() const;
    bool should_falsely_accuse_player() const;
    void update_count_value();
    bool is_max_updates_exceeded() const;
    void reset_values();
    static void notify_player_of_false_accusation(const Hash& crime);

    false_accusations();

    void do_update() override;
    static void falsely_accuse_player();

private:
    float initial_value_;
    float rate_;
    int update_count_;
    float coefficient_;
    bool accused_;
};
