#include "session.hpp"

namespace session {

    session::session(tcp::socket socket, ssl::context &ssl_context, session::handlers handlers)
            : ws_(std::move(socket), ssl_context), handlers_(std::move(handlers)) {
    }

    void session::handshake(std::optional<decltype(handlers::on_handshake)> handler) {
        do_handshake(decltype(handlers::on_handshake){
                .success = [handler](auto context) mutable {
                    context.owner->do_accept(std::move(handler));
                },
                .failure = handler.has_value() ? handler->failure : default_handlers::do_nothing(),
        });
    }

    void session::read() { do_read(); }

    void session::read(handler<handlers::context, std::tuple<std::string>,
            decltype(handlers::on_read)::FailureArgsPack> handler) {
        do_read(decltype(handlers::on_read){
                .success = [handler](auto context, auto bytes_transferred, auto data) {
                    handler.success(context, beast::buffers_to_string(data));
                },
                .failure = handler.failure
        });
    }

    void session::send(std::string message, std::optional<decltype(handlers::on_write)> handler) {
        do_write(asio::buffer(message), std::move(handler));
    }

    void session::do_handshake(std::optional<decltype(handlers::on_handshake)> handler) {
        ws_.next_layer().async_handshake(
                ssl::stream_base::server,
                [self = shared_from_this(), handler](boost::system::error_code ec) {
                    handlers::context context{self};

                    if (ec) {
                        self->handlers_.on_handshake.failure(context, ec);
                        if (handler.has_value())
                            handler->failure(context, ec);
                        return;
                    }

                    self->handlers_.on_handshake.success(context);
                    if (handler.has_value())
                        handler->success(context);
                }
        );
    }

    void session::do_accept(std::optional<decltype(handlers::on_accept)> handler) {
        ws_.async_accept(
                [self = shared_from_this(), handler](boost::system::error_code ec) {
                    handlers::context context{self};

                    if (ec) {
                        self->handlers_.on_accept.failure(context, ec);
                        if (handler.has_value())
                            handler->failure(context, ec);
                        return;
                    }

                    self->handlers_.on_accept.success(context);
                    if (handler.has_value())
                        handler->success(context);
                });
    }

    void session::do_read(std::optional<decltype(handlers::on_read)> handler) {
        ws_.async_read(
                buffer_,
                [self = shared_from_this(), handler = std::move(handler)]
                        (const beast::error_code &ec, std::size_t bytes_transferred) {
                    handlers::context context{self};

                    if (ec) {
                        self->handlers_.on_read.failure(context, bytes_transferred, ec);
                        if (handler.has_value())
                            handler->failure(context, bytes_transferred, ec);
                        return;
                    }

                    self->handlers_.on_read.success(context, bytes_transferred, self->buffer_.data());
                    if (handler.has_value())
                        handler->success(context, bytes_transferred, self->buffer_.data());
                }
        );
    }

    void session::do_write(const asio::const_buffer &data, std::optional<decltype(handlers::on_write)> handler) {
        ws_.async_write(
                data,
                [self = shared_from_this(), handler = std::move(handler)]
                        (const beast::error_code &ec, std::size_t bytes_transferred) {
                    handlers::context context{self};

                    if (ec) {
                        self->handlers_.on_write.failure(context, bytes_transferred, ec);
                        if (handler.has_value())
                            handler->failure(context, bytes_transferred, ec);
                        return;
                    }

                    self->handlers_.on_write.success(context, bytes_transferred);
                    if (handler.has_value())
                        handler->success(context, bytes_transferred);
                }
        );
    }
}