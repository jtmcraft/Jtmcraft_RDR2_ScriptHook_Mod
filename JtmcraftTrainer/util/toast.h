#pragma once
#include <string>

namespace toast {
    void objective(const std::string& text);
    void right(const char* text, const char* dict, const char* icon, const char* color, int duration);
    void right(const std::string& text, const std::string& dict, const std::string& icon);
    void headshot();
    void rampage();
}
