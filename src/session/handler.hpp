#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <type_traits>
#include <iostream>

namespace session {
    namespace handler_details {
        template<typename T>
        concept TupleTypePack = requires(T tuple) {
            typename std::tuple_size<T>::type;
        };

        template<typename Context, TupleTypePack ArgsPack, typename Result>
        struct handle_func_type_builder {
            handle_func_type_builder() = delete;

            template<typename... Args>
            using _handle_func_type = std::function<Result(Context, Args...)>;

            template<typename... Args>
            static _handle_func_type<Args...> unpack(const std::tuple<Args...> &) {}

            using handle_func_type = decltype(unpack(*static_cast<ArgsPack *>(nullptr)));
        };

        template<typename Context, TupleTypePack ArgsPack, typename Result>
        using handle_func_type = typename handle_func_type_builder<Context, ArgsPack, Result>::handle_func_type;
    }

    namespace default_handlers {
        struct do_nothing {
            template<typename... Args>
            /*implicit*/ operator std::function<void(Args...)>() &&{
                return [](Args...) {
                };
            }
        };

        struct just_say {
            std::string message;

            template<typename... Args>
            /*implicit*/ operator std::function<void(Args...)>() &&{
                return [message = std::move(message)](Args...) {
                    std::cout << message << std::endl;
                };
            }
        };

        template<size_t... arg_numbers>
        struct just_say_args_by_number {
            std::string message;

            template<typename... Args>
            /*implicit*/ operator std::function<void(Args...)>() &&{
                return [message = std::move(message)](Args &&... args) {
                    std::cout << message;
                    auto t = std::tuple(std::forward<Args>(args)...);
                    ((std::cout << std::get<arg_numbers>(t)), ...);
                    std::cout << std::endl;
                };
            }
        };

//        template <size_t arg_number, typename T = void>
//        struct just_say_arg {
//            std::string message;
//
//            template <typename... Args>
//            /*implicit*/ operator std::function<void(Args...)>() && {
//                return [message = std::move(message)](Args... args) {
//                    std::cout << message;
//                    std::cout << std::get<arg_number>(std::tuple(args...));
//                    std::cout << std::endl;
//
//                    static_assert(std::is_same_v<T, void> || std::is_convertible_v<decltype(std::get<arg_number>(std::tuple(std::forward<Args>(args)...))), T>,
//                                 "wrong type");
//                };
//            }
//        };

        template<typename ArgType, size_t Number = 0>
        struct just_say_arg {
            std::string message;

            template<typename... Args>
            /*implicit*/ operator std::function<void(Args...)>() &&{
                return [message = std::move(message)](Args... args) {
                    std::cout << message;

                    size_t i = 0;
                    ((handle_arg(i, args)), ...);

                    if (i <= Number) {
                        std::cout << "<just_say_arg: no found arg>";
                    }

                    std::cout << std::endl;
                };
            }

            ~just_say_arg() {} // to avoid a msvs error

        private:

            template<typename T>
            static void handle_arg(size_t &i, T &&arg) {
                if constexpr (std::is_convertible_v<decltype(arg), ArgType>) {
                    if (i == Number) {
                        std::cout << std::forward<T>(arg);
                    }
                    ++i;
                }
            }
        };
    }

    template<typename Context, handler_details::TupleTypePack SuccessArgs, handler_details::TupleTypePack FailureArgs>
    struct handler {
        handler_details::handle_func_type<Context, SuccessArgs, void> success;
        handler_details::handle_func_type<Context, FailureArgs, void> failure;

        using ContextType = Context;
        using SuccessArgsPack = SuccessArgs;
        using FailureArgsPack = FailureArgs;
    };
} // session

#endif //HANDLER_HPP
