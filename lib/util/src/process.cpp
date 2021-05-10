#include "process.hpp"

// std lib
#include <array>
#include <memory>
#include <cstdio>
#include <string>
#include <iostream>

namespace ott
{

namespace util 
{
    struct PipeCloser {
        void operator()(std::FILE* fp ) 
        {
            std::cout << "callable object to call \n";
            pclose(fp);
        }
    };
    Process::Process()  {}
    Process::Process(const std::string& cmd): cmd_(cmd) {}
    bool Process::invokes()
    {
        std::array<char,1024> buffer;
        std::unique_ptr<FILE, decltype(PipeCloser())> pipe(popen(cmd_.c_str(), "r"), PipeCloser());
        if (!pipe)
        {
            return false;
        }
        while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr )
        {
            this->result_ += buffer.data();
        }
        return true;
    }

    Process& Process::operator<<(const std::string& s)
    {
        this->cmd_ += std::string(" ") + s; 
        return *this;
    }
    Process::~Process() {}

    std::string Process::result() const
    {
        return this->result_;
    }

   
} // end of Util namespace
} // end of Ott namespace
