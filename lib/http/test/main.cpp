#include <iostream>
#include <string>
#include "../src/server.hpp"

#if !defined(_WIN32)
#include <thread>
#include <signal.h>

int main(int argc, char* argv[])
{
  try
  {
    // Check command line arguments.
    /*if (argc != 5)
    {
      std::cerr << "Usage: http_server <address> <port> <threads> <doc_root>\n";
      std::cerr << "  For IPv4, try:\n";
      std::cerr << "    receiver 0.0.0.0 80 1 .\n";
      std::cerr << "  For IPv6, try:\n";
      std::cerr << "    receiver 0::0 80 1 .\n";
      return 1;
    }*

    // Block all signals for background thread.
    /*sigset_t new_mask;
    sigfillset(&new_mask);
    sigset_t old_mask;
    pthread_sigmask(SIG_BLOCK, &new_mask, &old_mask);*/

    // Run server in background thread.
    //std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[3]);
    //ott::server::Server s(argv[1], argv[2], argv[4]);
    ott::http::server s("0.0.0.0", "8080");
    s.run();
    //boost::thread t(boost::bind(&ott::server::Server::run, &s));

    // Restore previous signals.
    /*pthread_sigmask(SIG_SETMASK, &old_mask, 0);

    // Wait for signal indicating time to shut down.
    sigset_t wait_mask;
    sigemptyset(&wait_mask);
    sigaddset(&wait_mask, SIGINT);
    sigaddset(&wait_mask, SIGQUIT);
    sigaddset (& wait_mask, SIGTERM);
    pthread_sigmask(SIG_BLOCK, &wait_mask, 0);
    int sig = 0;
    sigwait(&wait_mask, &sig);

    // Stop the server.
    //s.stop();*/
    //t.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}

#endif // !defined(_WIN32)
