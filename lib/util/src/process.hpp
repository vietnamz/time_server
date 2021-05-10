/*
 * Abstract class to trigger a bash process executable.
 *
 *
 *
 * required: c++14 or onward
 */
#pragma once

#include <string>


namespace ott
{
    namespace util
    {
        class Process 
        {
        public:
            // default constructor
            Process();
            virtual ~Process();
            Process(const Process& other ) = delete;
            Process(Process&& other) = delete;
            Process& operator=(const Process& other) = delete; 
            /*
             *  cunstructor with a process name
             */ 
            Process(const std::string& );

            /*
             * override stream operator.
             *
             */
            Process& operator<<(const std::string& s);

            /*
             * To invoke the execution from the caller.
             */
            virtual bool invokes();

            /*
             * retrieve the result string
             */
            std::string result() const;

        private:
            std::string cmd_;
            std::string result_;
        };
    }
}


