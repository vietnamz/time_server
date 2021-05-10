//
// Created by john on 09/05/2021.
//

#include "timer.hpp"

#include <string>
#include <string_view>
#include <thread>

namespace ott
{
    namespace websocket
    {
        timer make_timer()
        {
            auto result = co_await wail_every_5_secs();
            co_return result;
        }
    }
}