//
// Created by john on 07/05/2021.
//

#pragma once

#include <string>

namespace ott {
    namespace http {
        class server {
        public:
            server() = default;
            server(const std::string host, const std::string port) : host_(host), port_(port) {}
            void run();

        private:
            std::string host_;
            std::string port_;
        };
    }
}
