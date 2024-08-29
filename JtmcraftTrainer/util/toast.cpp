#include "toast.h"

#include "util.h"
#include "../../../inc/natives.h"

struct ui_feed_parameters0
{
    alignas(8) int duration;
    alignas(8) const char* dict;
    alignas(8) const char* sound;
    alignas(8) int internal_code;
};

struct ui_feed_parameters1
{
    alignas(8) int internal_code0;
    alignas(8) const char* text;
    alignas(8) const char* dict;
    alignas(8) Hash icon;
    alignas(8) int internal_code1;
    alignas(8) Hash color;
    alignas(8) int internal_code2;
};
    

ui_feed_parameters0 set_ui_feed_parameters0(const int duration) {
    ui_feed_parameters0 params;
    params.duration = duration;
    params.dict = util::create_string("Transaction_Feed_Sounds");
    params.sound = util::create_string("Transaction_Positive");
    params.internal_code = 0;
    return params;
}

ui_feed_parameters1 set_ui_feed_parameters1(const char* text, const char* dict, const char* icon, const char* color) {
    ui_feed_parameters1 params;
    params.internal_code0 = 0;
    params.text = util::create_string(text);
    params.dict = util::create_string(dict);
    params.icon = util::get_hash(icon);
    params.internal_code1 = 1;
    params.color = util::get_hash(color);
    params.internal_code2 = 0;
    return params;
}

void toast::objective(const std::string& text) {
    UILOG::_0xFA233F8FE190514C(reinterpret_cast<Any*>(util::create_string(text)));
    UILOG::_0xE9990552DEC71600();
    UILOG::_0xA3108D6981A5CADB();
    UILOG::_0xDFF0D417277B41F8();
}

void toast::right(const char* text, const char* dict, const char* icon, const char* color, const int duration) {
    ui_feed_parameters0 notification_parameters0 = set_ui_feed_parameters0(duration);
    ui_feed_parameters1 notification_parameters1;
    notification_parameters1 = set_ui_feed_parameters1(text, dict, icon, color);
    UIUNK::_0xB249EBCB30DD88E0(reinterpret_cast<Any*>(&notification_parameters0),
                               reinterpret_cast<Any*>(&notification_parameters1), true);
}

void toast::right(const std::string& text, const std::string& dict, const std::string& icon) {
    right(text.c_str(), dict.c_str(), icon.c_str(), "COLOR_PURE_WHITE", 1500);
}

void toast::headshot() {
    right("Head shot", "toast_awards_set_h", "awards_set_h_006");
}

void toast::rampage() {
    right("Rampage", "mp_lobby_textures", "leaderboard_gold");
}
