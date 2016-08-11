#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <signal.h>
#include <sstream>
#include <thread>
#include <chrono>

void signal_thread_handler(sigset_t &sigset) {
    while (true) {
        int sig{0};
        int ret = sigwait(&sigset, &sig);
        if (0 != ret) {
            char buffer[2048];
            snprintf(buffer, sizeof(buffer)-1, "sigwait failed with ret[%d]", ret);
            perror(buffer);
            continue;
        }
        std::cerr << "signal[" << sig << "] caught; do nothing" << std::endl;
    }
}

int main(int argc, char** argv) {
    signal(SIGPIPE, SIG_IGN);
    sigset_t sigset;
    sigaddset(&sigset, SIGTERM);
    sigaddset(&sigset, SIGINT);
    int ret = pthread_sigmask(SIG_SETMASK, &sigset, NULL); // pending specified signals
    if (0 != ret) {
        std::ostringstream  oss;
        oss << "pthread_sigmask failed with ret[" << ret << "]";
        perror(oss.str().c_str());
        return 1;
    }
    std::thread signal_thread(signal_thread_handler, std::ref(sigset));
    signal_thread.detach();
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}
