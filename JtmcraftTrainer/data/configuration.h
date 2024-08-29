#pragma once

#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>

#include "../json.h"
#include "../util/logger.h"

class configuration {
    configuration() = default;
    ~configuration() = default;

    nlohmann::json config_json_;
    std::mutex config_mutex_;
    
public:
    configuration(configuration const&) = delete;
    configuration& operator=(configuration const&) = delete;

    static configuration& get_instance() {
        static configuration instance;
        return instance;
    }

    void load(const std::string& filename) {
        std::lock_guard<std::mutex> lock(config_mutex_);
        
        std::ifstream file(filename);
        std::stringstream message;
        
        if (file.is_open()) {
            file >> config_json_;
            file.close();    
            message << "Loaded config file: " << filename;            
        }
        else {
            message << "Cannot open config file: " << filename;
        }

        logger::log_info(message.str());
    }

    static std::vector<std::string> split(const std::string &s, const char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream token_stream(s);
        while (std::getline(token_stream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    template <typename T>
    T get_or_else(const std::string& key, T else_value) {
        std::lock_guard<std::mutex> lock(config_mutex_);
        nlohmann::json* j = &config_json_;

        const std::vector<std::string> keys = split(key, '.');
        try {
            for (const auto& k : keys) {
                j = &j->at(k);
            }
            
            T value;
            j->get_to(value);
            
            return value;
        } catch (nlohmann::json::exception& json_exception) {
            std::cerr << json_exception.what() << '\n';
            
            return else_value;
        }
    }
};
