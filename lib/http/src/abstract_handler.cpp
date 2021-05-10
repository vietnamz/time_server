//
// Created by john on 08/05/2021.
//

#include "abstract_handler.hpp"

//! boost
#include <boost/assert.hpp>

namespace ott
{
    namespace http
    {
        handler& abstract_handler::next() {
            BOOST_ASSERT(next_ != nullptr);
            return *(next_);
        }
        void abstract_handler::set_next(std::shared_ptr<handler> next) {
            BOOST_ASSERT(next.get() != nullptr);
            next_ = next;
        }
        bool abstract_handler::operator()(const std::string_view) {
            return false;
        }
    }
}