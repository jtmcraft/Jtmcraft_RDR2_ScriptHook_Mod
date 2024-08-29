#include "util.h"

#include <chrono>
#include <iomanip>
#include <sstream>

#include "../../../inc/natives.h"

Hash util::get_hash(const std::string& key) {
    return GAMEPLAY::GET_HASH_KEY(const_cast<char*>(key.c_str()));
}

char* util::create_string(const std::string& value) {
    return GAMEPLAY::CREATE_STRING(10, const_cast<char*>("LITERAL_STRING"), const_cast<char*>(value.c_str()));
}

char* util::color_string(const std::string& value) {
    return GAMEPLAY::CREATE_STRING(42, const_cast<char*>("LITERAL_STRING"), const_cast<char*>(value.c_str()));
}


std::string util::format_float_value(const float float_value) {
    constexpr int fixed_width = 10;
    constexpr int fixed_precision = 4;
    std::stringstream stream;
    
    stream << std::right << std::setw(fixed_width) << std::fixed << std::setprecision(fixed_precision) << float_value;
    
    return stream.str();
}

std::string util::format_coords(const Vector3& coords) {
    std::stringstream stream;
    stream << format_float_value(coords.x) << ", "
    << format_float_value(coords.y) << ", "
    << format_float_value(coords.z);

    return stream.str();
}

std::string util::get_current_timestamp() {
    const auto time_point = std::chrono::system_clock::now();
    const std::time_t time_now = std::chrono::system_clock::to_time_t(time_point);
    std::tm now_tm = {};

    const errno_t failure = localtime_s(&now_tm, &time_now);
    if (!failure) {
        std::ostringstream stream;
        stream << std::put_time(&now_tm, "** %Y-%m-%d %H:%M:%S");

        return stream.str();        
    }

    std::stringstream error_message;
    error_message << "GetCurrentTimestamp() failed with error " << failure <<  '\n';
    return error_message.str();
}

std::string util::add_timestamp_to_message(const std::string& message) {
    std::stringstream timestamped_message;
    
    timestamped_message << "[" << get_current_timestamp() << "] " << message << '\n';
    
    return timestamped_message.str();
}
