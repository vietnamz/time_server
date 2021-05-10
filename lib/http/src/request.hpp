#pragma once

#include <string>
#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/buffer.hpp>

#include "mine_types.hpp"
#include "time_handler.hpp"
namespace ott

{
    namespace http
    {


        std::string pathCat(boost::beast::string_view base, boost::beast::string_view path);

        std::shared_ptr<handler> get_handlers();

        // This function produces an HTTP response for the given
        // request. The type of the response object depends on the
        // contents of the request, so the interface requires the
        // caller to pass a generic lambda for receiving the response
        template<class Body, class Allocator, class Send>
        void handleRequest(boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>>&& req, Send&& send)
        {
            std::cout << "start handleRequest " << std::endl;
            auto const bad_request =
                [&req](boost::beast::string_view why)
                {
                    boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::bad_request, req.version()};
                    res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
                    res.set(boost::beast::http::field::content_type, "text/html");
                    res.keep_alive(req.keep_alive());
                    res.body() = std::string(why);
                    res.prepare_payload();
                    return res;
                };
            auto const not_found =
                [&req](boost::beast::string_view target)
                {
                    boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::not_found, req.version()};
                    res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
                    res.set(boost::beast::http::field::content_type, "text/html");
                    res.keep_alive(req.keep_alive());
                    res.body() = "The resource '" + std::string(target) + "' was not found.";
                    res.prepare_payload();
                    return res;
                };

            // Returns a server error response
            auto const server_error =
            [&req](boost::beast::string_view what)
            {
                boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::internal_server_error, req.version()};
                res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
                res.set(boost::beast::http::field::content_type, "text/html");
                res.keep_alive(req.keep_alive());
                res.body() = "An error occurred: '" + std::string(what) + "'";
                res.prepare_payload();
                return res;
            };

            // Make sure we can handle the method
            if( req.method() != boost::beast::http::verb::get &&
                req.method() != boost::beast::http::verb::head)
                return send(bad_request("Unknown HTTP-method"));

            // Request path must be absolute and not contain "..".
            if( req.target().empty() ||
                req.target()[0] != '/' ||
                req.target().find("..") != boost::beast::string_view::npos)
                return send(bad_request("Illegal request-target"));


            // Attempt to open the file
            boost::beast::error_code ec;


            // Handle an unknown error
            if(ec)
                return send(server_error(ec.message()));

            std::string result;
            std::shared_ptr<handler> handler = get_handlers();
            std::string_view target = std::string_view(req.target().data(), req.target().size());
            if(!(*handler)(target)) {
                std::cout << "not found the " << target << std::endl;
                return send(not_found(req.target()));
            } else {
                std::cout << "found the " << target << std::endl;
                result = handler->result(target);
                std::cout << "result:  " << target << std::endl;
            }
            auto const size = result.size();

            // Respond to HEAD request
            if(req.method() == boost::beast::http::verb::head)
            {
                boost::beast::http::response<boost::beast::http::empty_body> res{boost::beast::http::status::ok, req.version()};
                res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
                res.set(boost::beast::http::field::content_type, "application/json");
                res.content_length(size);
                res.keep_alive(req.keep_alive());
                return send(std::move(res));
            }
            boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::ok, req.version()};
            res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(boost::beast::http::field::content_type, "application/json");
            res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
            res.content_length(result.size());
            res.body() = result;
            res.prepare_payload();
            return send(std::move(res));
        }

        // report a failure
        void fail(boost::beast::error_code ec, char const* what);

    } // http namespace
} // ott namespace
