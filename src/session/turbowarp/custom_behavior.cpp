#include <spdlog/spdlog.h>

#include "session/turbowarp/methods.hpp"

using namespace turbowarp::method;

/*
 * Это пример обработки запросов
 * Желательно делать изменения здесь
 */

turbowarp::Result<std::string> Handshake::custom_behavior(boost::json::value const &value) {
    for (auto param : this->params) {
        spdlog::debug("{} : {}", param, boost::json::value_to<std::string>(value.at(param)));
    }

    if (false) {
        boost::json::value jv = {
            {"method", "handshake"},
            {"project_id", "123"},
            {"user", "larinenok"},
        };

        return Some<std::string>(boost::json::serialize(jv));
    }

    if (false) {
        return Error<std::string>(JsonParser::error_message("Generic Error", 4000));
    }

    return None<std::string>();
}

turbowarp::Result<std::string> Set::custom_behavior(boost::json::value const &value) {
    for (auto param : this->params) {
        spdlog::debug("{} : {}", param, boost::json::value_to<std::string>(value.at(param)));
    }

    if (false) {
        return Error<std::string>(JsonParser::error_message("Generic Error", 4000));
    }

    return None<std::string>();
}

turbowarp::Result<std::string> Create::custom_behavior(boost::json::value const &value) {
    for (auto param : this->params) {
        spdlog::debug("{} : {}", param, boost::json::value_to<std::string>(value.at(param)));
    }

    if (false) {
        return Error<std::string>(JsonParser::error_message("Generic Error", 4000));
    }

    return None<std::string>();
}

turbowarp::Result<std::string> Rename::custom_behavior(boost::json::value const &value) {
    for (auto param : this->params) {
        spdlog::debug("{} : {}", param, boost::json::value_to<std::string>(value.at(param)));
    }

    if (false) {
        return Error<std::string>(JsonParser::error_message("Generic Error", 4000));
    }

    return None<std::string>();
}

turbowarp::Result<std::string> Delete::custom_behavior(boost::json::value const &value) {
    for (auto param : this->params) {
        spdlog::debug("{} : {}", param, boost::json::value_to<std::string>(value.at(param)));
    }

    if (false) {
        return Error<std::string>(JsonParser::error_message("Generic Error", 4000));
    }

    return None<std::string>();
}