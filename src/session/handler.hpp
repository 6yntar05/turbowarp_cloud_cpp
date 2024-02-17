#pragma once

#include <iostream>
#include <type_traits>

namespace session {

namespace handler_details {

template <typename T>
concept TupleTypePack = requires(T tuple) {
    // in theory, it should break down there is T not std::tuple
    typename std::tuple_size<T>::type;
};

namespace details {

template <typename Context, TupleTypePack ArgsPack, typename Result>
struct handle_func_type_builder {
private:
    handle_func_type_builder() = delete;

    template <typename... Args>
    using _handle_func_type = std::function<Result(Context, Args...)>;

    template <typename... Args>
    static auto unpack(const std::tuple<Args...> &) -> _handle_func_type<Args...>;

public:
    using handle_func_type = decltype(unpack(std::declval<ArgsPack>()));
};

}  // namespace details

template <typename Context, TupleTypePack ArgsPack, typename Result>
using handle_func_type =
    typename details::handle_func_type_builder<Context, ArgsPack, Result>::handle_func_type;

}  // namespace handler_details

namespace default_handlers {

struct do_nothing {
    template <typename... Args>
    /*implicit*/ operator std::function<void(Args...)>() && {
        return [](Args...) {};
    }
};

struct just_say {
    std::string message;

    template <typename... Args>
    /*implicit*/ operator std::function<void(Args...)>() && {
        return [message = std::move(message)](Args...) { std::cout << message << std::endl; };
    }
};

template <size_t... ArgsNumbers>
struct just_say_args_by_numbers {
    std::string message;

    template <typename... Args>
    /*implicit*/ operator std::function<void(Args...)>() && {
        return [message = std::move(message)](Args &&...args) {
            std::cout << message;
            auto t = std::tuple(std::forward<Args>(args)...);
            ((std::cout << std::get<ArgsNumbers>(t)), ...);
            std::cout << std::endl;
        };
    }
};

template <typename ArgType, size_t Number = 0>
struct just_say_arg {
    std::string message;

    template <typename... Args>
    /*implicit*/ operator std::function<void(Args...)>() && {
        return [message = std::move(message)](Args... args) {
            std::cout << message;

            size_t i = 0;
            ((handle_arg(i, args)), ...);

            std::cout << std::endl;

            static_assert(Number < (std::is_convertible_v<Args, ArgType> + ...),
                          "there are fewer such types in arguments");
        };
    }

    ~just_say_arg() {}  // to avoid a msvs error

private:
    template <typename T>
    static void handle_arg(size_t &i, T &&arg) {
        if constexpr (std::is_convertible_v<decltype(arg), ArgType>) {
            if (i == Number) {
                std::cout << std::forward<T>(arg);
            }
            ++i;
        }
    }
};

}  // namespace default_handlers

template <typename Context, handler_details::TupleTypePack SuccessArgs,
          handler_details::TupleTypePack FailureArgs>
struct handler {
    handler_details::handle_func_type<Context, SuccessArgs, void> success;
    handler_details::handle_func_type<Context, FailureArgs, void> failure;

    using ContextType = Context;
    using SuccessArgsPack = SuccessArgs;
    using FailureArgsPack = FailureArgs;
};

}  // namespace session
