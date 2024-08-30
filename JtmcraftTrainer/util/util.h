#pragma once
#include <string>

#include "../../inc/types.h"

namespace util {
    Hash get_hash(const std::string& key);
    char* create_string(const std::string& value);
    char* color_string(const std::string& value);
    std::string format_float_value(float float_value);
    std::string format_coords(const Vector3& coords);
    std::string get_current_timestamp();
    std::string add_timestamp_to_message(const std::string& message);

    template<typename T> T clamp(T value, T min, T max);
}

template<typename T>
T util::clamp(const T value, const T min, const T max) {
    static_assert(std::is_arithmetic_v<T>, "Numeric type required");
    
    if (value < min) {
        return min;
    }
        
    if (value > max) {
        return max;
    }
        
    return value;
}
