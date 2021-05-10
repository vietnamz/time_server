//
// Created by john on 07/05/2021.
//

#include "server.hpp"

//! stl
#include <thread>

//! boost
#include <boost/asio/ip/tcp.hpp>
#include <boost/config.hpp>
#include <boost/bind/bind.hpp>

//! local
#include "listener.hpp"

namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


using namespace std;
namespace ott {
    namespace http {
        void server::run()
        {
            auto const address = net::ip::make_address(host_);
            auto const port = static_cast<unsigned short>(std::atoi(port_.c_str()));
            auto const num_thread = 20;
            net::io_context ioc{num_thread};
            // Create and launch a listening port
            std::make_shared<listener>(
                    ioc,
                    tcp::endpoint{address, port})->run();

            // Run the I/O service on the requested number of threads
            std::vector<std::thread> v;
            v.reserve(num_thread - 1);
            for(auto i = num_thread - 1; i > 0; --i)
                v.emplace_back(
                        [&ioc]
                        {
                            ioc.run();
                        });
            ioc.run();
        }
    }
}