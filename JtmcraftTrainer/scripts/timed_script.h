#pragma once

class timed_script
{
    int interval_;
    int units_;
    bool updated_;

    bool should_update() const;

public:
    explicit timed_script(int interval);
    virtual ~timed_script() = default;
    timed_script(const timed_script&) = delete;
    timed_script& operator =(const timed_script&) = delete;
    timed_script(timed_script&&) = delete;
    timed_script& operator=(timed_script&&) = delete;

    void on_update();
    void on_reset();
    int get_interval() const;
    void set_interval(int interval);

    virtual void do_update() = 0;
};
