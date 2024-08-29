#pragma once
#include "timed_script.h"

class rainbow_lantern final : public timed_script
{
public:
    explicit rainbow_lantern(int interval);
    void do_update() override;
    
private:
    int counter_;
};
