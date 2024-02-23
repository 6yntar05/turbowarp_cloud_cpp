#pragma once

#include <boost/json.hpp>
#include <iostream>
#include <list>

#include "session/turbowarp/json_parser.hpp"
#include "session/turbowarp/methods.hpp"
#include "session/turbowarp/result.hpp"

namespace turbowarp {
void test_requests() {
    method::AvailableMethods::methods = {
        {"handshake", std::make_shared<method::Handshake>()},
        {"set", std::make_shared<method::Set>()},
        {"create", std::make_shared<method::Create>()},
        {"rename", std::make_shared<method::Rename>()},
        {"delete", std::make_shared<method::Delete>()},
    };
    // or
    // method::AvailableMethods::base_init();

    {
        boost::json::value jv = {
            {"method", "handshake"},
            {"project_id", "123"},
            {"user", "larinenok"},
        };

        auto answer = turbowarp::JsonParser::analize_data(boost::json::serialize(jv));
        if (answer.is_type(turbowarp::Type::Some)) std::cout << answer.get() << std::endl;
    }

    {
        boost::json::value jv = {
            {"method", "set"},
            {"name", "123"},
            {"value", "larinenok"},
        };

        auto answer = turbowarp::JsonParser::analize_data(boost::json::serialize(jv));
        if (answer.is_type(turbowarp::Type::Some)) std::cout << answer.get() << std::endl;
    }

    {
        boost::json::value jv = {
            {"method", "create"},
            {"name", "123"},
            {"value", "larinenok"},
        };

        auto answer = turbowarp::JsonParser::analize_data(boost::json::serialize(jv));
        if (answer.is_type(turbowarp::Type::Some)) std::cout << answer.get() << std::endl;
    }

    {
        boost::json::value jv = {
            {"method", "rename"},
            {"name", "123"},
            {"new_name", "larinenok"},
        };

        auto answer = turbowarp::JsonParser::analize_data(boost::json::serialize(jv));
        if (answer.is_type(turbowarp::Type::Some)) std::cout << answer.get() << std::endl;
    }

    {
        boost::json::value jv = {
            {"method", "delete"},
            {"name", "123"},
        };

        auto answer = turbowarp::JsonParser::analize_data(boost::json::serialize(jv));
        if (answer.is_type(turbowarp::Type::Some)) std::cout << answer.get() << std::endl;
    }

    {
        boost::json::value jv = {
            {"method", "asd"},
        };

        auto answer = turbowarp::JsonParser::analize_data(boost::json::serialize(jv));
        if (answer.is_type(turbowarp::Type::Some)) std::cout << answer.get() << std::endl;
        if (answer.is_type(turbowarp::Type::Error)) std::cout << answer.get() << std::endl;
    }
}
}  // namespace turbowarp