//
// Created by john on 08/05/2021.
//

#pragma once

//! stl
#include <string>
#include <memory>

//! local
#include "handler.hpp"

namespace ott
{
    namespace http
    {
        class abstract_handler : public handler {
        public:
            abstract_handler() = default;
            abstract_handler(const std::string_view& base) : base_(base) {}
            virtual handler& next() override;
            virtual void set_next(std::shared_ptr<handler> next) override;
            virtual bool operator()(const std::string_view) override;
            virtual std::string result(const std::string_view& context)
            {
                if(base_ != context) {
                    if (next_.get() == nullptr) {
                        return std::string();
                    }
                    return next_->result(context);
                }
                return result_;
            }
            virtual std::string_view base() {
                return base_;
            }
            virtual bool is_valid(const std::string_view&) override{
                return false;
            }

        protected:
            std::shared_ptr<handler> next_;
            std::string_view base_;
            std::string result_;
        };
    }
}
