#ifndef TEST_MAIN_HPP
#define TEST_MAIN_HPP

#include "standart_headers.hpp"

#include "session/listener.hpp"
#include "session/session.hpp"
#include "session/server.hpp"
#include "session/handler.hpp"

namespace session {

    void minimal_session(tcp::socket socket, ssl::context &ctx) {
        try {
            // Создаем WebSocket стрим с SSL
            websocket::stream<ssl::stream<tcp::socket>> ws{std::move(socket), ctx};

            // Переключаемся на режим WebSocket через SSL
            ws.next_layer().handshake(ssl::stream_base::server);
            ws.accept();

            for (;;) {
                boost::beast::multi_buffer buffer;

                // Чтение сообщения
                ws.read(buffer);

                // Отправка эхо-ответа
                ws.text(ws.got_text());
                ws.write(buffer.data());
            }
        } catch (boost::system::system_error const &se) {
            if (se.code() != websocket::error::closed)
                std::cerr << "Error: " << se.code().message() << std::endl;
        } catch (std::exception const &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    void minimal_ws() {
        try {
            asio::io_context ioc;
            tcp::acceptor acceptor{ioc, {tcp::v4(), 443}};
            ssl::context ctx{ssl::context::tlsv13_server};

            // Загрузка сертификата и ключа
            ctx.use_certificate_chain_file("../../server.crt");
            ctx.use_private_key_file("../../server.key", ssl::context::pem);

            for (;;) {
                // Принятие нового соединения
                tcp::socket socket{ioc};
                acceptor.accept(socket);

                // Создание нового потока для обработки соединения
                std::thread([&ctx, s = std::move(socket)]() mutable {
                    minimal_session(std::move(s), ctx);
                }).detach();
            }

        } catch (std::exception const &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }

    void normal_ws() {
        using namespace session;

        boost::asio::io_context io_context(1);

        // todo: make paths
        boost::asio::ssl::context ctx{boost::asio::ssl::context::tlsv13};
        ctx.use_certificate_chain_file("../../server.crt");
        ctx.use_private_key_file("../../server.key", boost::asio::ssl::context::pem);

        auto server_ = std::make_shared<server>(io_context, server::config_t{
                .endpoint = {asio::ip::make_address("127.0.0.1"), 8080},
                .ssl_context = ctx,
        });

        server_->run();
        io_context.run();
    }

}

#endif