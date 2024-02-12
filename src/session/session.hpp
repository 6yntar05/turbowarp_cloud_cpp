#ifndef SESSION_HPP
#define SESSION_HPP

#include "standard_headers.hpp"

namespace session {
    class session : public std::enable_shared_from_this<session> {

        ////// types
    public:
        struct handlers {
            struct context {
                const shared_ptr<session> &owner;

            };

            handler<context, std::tuple<>, std::tuple<const beast::error_code &>> on_handshake = {
                    .success = default_handlers::just_say("handshake success"),
                    .failure = default_handlers::just_say_arg<beast::error_code>("handshake error: "),
            };

            handler<context, std::tuple<>, std::tuple<const beast::error_code &>> on_accept = {
                    .success = default_handlers::just_say("accept success"),
                    .failure = default_handlers::just_say_arg<beast::error_code>("accept error: "),
            };

            handler<context,
                    std::tuple<size_t /*bytes_transferred*/, asio::const_buffer>,
                    std::tuple<size_t /*bytes_transferred*/, const beast::error_code &>
            > on_read = {
                    .success = default_handlers::just_say("read success"),
                    .failure = default_handlers::just_say_arg<beast::error_code>("read error: "),
            };

            handler<context,
                    std::tuple<size_t /*bytes_transferred*/>,
                    std::tuple<size_t /*bytes_transferred*/, const beast::error_code &>
            > on_write = {
                    .success = default_handlers::just_say("write success"),
                    .failure = default_handlers::just_say_arg<beast::error_code>("write error: "),
            };

        };

        ////// fields
    private:
        websocket::stream<ssl::stream<tcp::socket>> ws_;
        beast::flat_buffer buffer_;
        handlers handlers_;

        ////// public methods
    public:
        explicit session(tcp::socket socket, ssl::context &ssl_context, handlers handlers);

        // make lazy?
        void handshake(std::optional<decltype(handlers::on_handshake)> handler = {});

        void read();

        void read(handler<handlers::context, std::tuple<std::string>,
                decltype(handlers::on_read)::FailureArgsPack> handler);

        void send(std::string message, std::optional<decltype(handlers::on_write)> handler = {});

        ////// inner methods
    private:
        void do_handshake(std::optional<decltype(handlers::on_handshake)> handler = {});

        void do_accept(std::optional<decltype(handlers::on_accept)> handler = {});

        void do_read(std::optional<decltype(handlers::on_read)> handler = {});

        void do_write(const asio::const_buffer &data, std::optional<decltype(handlers::on_write)> handler = {});

    };
} // session

#endif //SESSION_HPP
