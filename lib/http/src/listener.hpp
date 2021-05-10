//
// Created by john on 08/05/2021.
//

#pragma once

//! boost
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

//! local
#include "session.hpp"


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


namespace ott
{
    namespace http {


        class listener : public std::enable_shared_from_this<listener> {

        private:
            net::io_context& ioc_;
            tcp::acceptor acceptor_;
        public:
            listener(
                    net::io_context& ioc,
                    tcp::endpoint endpoint);
            // Start accepting incoming connections
            void run();
        private:
            void do_accept();
            void on_accept(beast::error_code ec, tcp::socket socket);
        };
    }
}
