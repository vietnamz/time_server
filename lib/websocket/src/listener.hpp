//
// Created by john on 08/05/2021.
//

#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace ott
{
    namespace websocket
    {
    class listener : public std::enable_shared_from_this<listener> {
        private:
            net::io_context& ioc_;
            tcp::acceptor acceptor_;
        public:
            listener(
                    net::io_context& ioc,
                    tcp::endpoint endpoint);
            virtual void run();

        private:
            void do_accept();
            void on_accept(beast::error_code ec, tcp::socket socket);
        };
    }
}

