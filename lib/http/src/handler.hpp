//
// Created by john on 08/05/2021.
//

#pragma once

#include <unordered_map>
#include <memory>
#include <string>

 namespace ott
 {
    namespace http
    {

        /*
         *
         *  pure virtual abstract class to accommodate chain of responsibility.
         */
        class handler
        {
        public:
            /*!
             *  take the next handler in the chain.
             *
             */
            virtual handler& next() = 0;

            /*!
             *  set the next handler in the chain.
             *
             */
            virtual void set_next(std::shared_ptr<handler> next) = 0;

            /*!
             *
             *  the execution.
             *
             * @return failed or success
             */
            virtual bool operator()(const std::string_view) = 0;

            /*!
             *
             * take the result back to caller.
             * @return string
             */
            virtual std::string result(const std::string_view &) = 0;

            /*!
             * set the url base. such as /time.
             * @return
             */
            virtual std::string_view base() = 0 ;
            /*!
             *
             *  is the handler is valid.
             * @return true or false.
             */
            virtual bool is_valid(const std::string_view&)  = 0 ;
        };
    }
 }
