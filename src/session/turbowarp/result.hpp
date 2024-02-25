#pragma once

namespace turbowarp {
enum class Type { Some, None, Error };

template <typename T>
class Result {
public:
    Result(T const &data, Type const &type) : data(data), type(type) {}
    Result(Result const &result) : Result(result.data, result.type) {}

    bool is_type(Type const &type) { return this->type == type; };

    T get() { return this->data; }

private:
    T data;
    Type type;
};

template <typename T>
class Some : public Result<T> {
public:
    Some(T const &data) : Result<T>(data, Type::Some) {}
};

template <typename T>
class None : public Result<T> {
public:
    None() : Result<T>(T(), Type::None) {}
};

template <typename T>
class Error : public Result<T> {
public:
    Error(T const &data) : Result<T>(data, Type::Error) {}
};
}  // namespace turbowarp