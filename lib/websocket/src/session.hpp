//
// Created by john on 09/05/2021.
//

#pragma once

//!stl
#include <memory>
#include <string>

//! boost
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio.hpp>

#include "timer.hpp"


namespace beast = boost::beast;         // from <boost/beast.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace ott
{
    namespace websocket
    {
        class session : public std::enable_shared_from_this<session>{
        private:
            beast::websocket::stream<beast::tcp_stream> ws_;
            beast::flat_buffer buffer_;
            std::string time_;
            //timer t;
        public:
            explicit session(tcp::socket&& socket);
            virtual ~session() noexcept;
            virtual void run();
            virtual void on_run();
            virtual void on_accept(beast::error_code ec);
            virtual void do_read();
            virtual void on_read(beast::error_code ec, std::size_t bytes_transferred);
            virtual void on_write(beast::error_code ec, std::size_t bytes_transferred);
            virtual void do_schedule();
        };
    }
}


