//
// Created by john on 08/05/2021.
//

#pragma once

//! local
#include "abstract_handler.hpp"

namespace ott {
    namespace http {

        class time_handler : public abstract_handler {
        public:
            time_handler(const std::string_view& context) : abstract_handler(context) {};
            time_handler(time_handler* other) : abstract_handler(other->base()) {};
            time_handler() = default;
            bool operator()(const std::string_view) override;
            bool is_valid(const std::string_view& context) override{
                return base_ == context;
            }
        };
    }
}