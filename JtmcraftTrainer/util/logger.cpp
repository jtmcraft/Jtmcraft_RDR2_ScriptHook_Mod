#include "logger.h"

#include <iostream>

#include "util.h"

void logger::log_info(const std::string& message) {
    std::cout << util::add_timestamp_to_message(message);
}
