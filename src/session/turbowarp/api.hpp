#pragma once

#include <boost/json.hpp>
#include <string>
#include <map>

namespace turbowarp {
        class JsonParser {
            public:
                static std::string analize_data(std::string data);
            private:
                static std::string ok_message;

                static std::string error_message(std::string name, int status);
        };

        namespace method {
            struct Params {
                std::vector<std::string> names;
            };

            struct BaseMethod {
                std::string method;
                std::map<std::string, std::string> values;

                BaseMethod(Params params, boost::json::value const &v) {
                    for (auto p : params.names) {
                        this->values.insert({p, boost::json::value_to<std::string>(v.at(p))});
                    }
                }
            };

            struct Handshake : BaseMethod {
                static Params params;

                Handshake(boost::json::value const &v) : BaseMethod(params, v) {}
            };

            struct Set : BaseMethod {
                static Params params;

                Set(boost::json::value const &v) : BaseMethod(params, v) {}
            };

            struct Create : BaseMethod {
                static Params params;

                Create(boost::json::value const &v) : BaseMethod(params, v) {}
            };

            struct Rename : BaseMethod {
                static Params params;

                Rename(boost::json::value const &v) : BaseMethod(params, v) {}
            };

            struct Delete : BaseMethod {
                static Params params;

                Delete(boost::json::value const &v) : BaseMethod(params, v) {}
            };

            static bool is_valid(Params const &mp, boost::json::value const &v) {
                try {
                    for (auto value : mp.names) {
                        boost::json::value_to<std::string>(v.at(value));
                    }
                } catch(...) {
                    return false;
                }

                return true;
            }
        } // namespace method
} // namespace turbowarp