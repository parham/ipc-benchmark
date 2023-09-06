
#include <memory>
#include <iostream>
#include <chrono>
#include <string>

#include <common/core.h>
#include <boost_shm/boost_shm.h>
#include <named_pipe/named_pipe.h>
#include <domain_socket/domain_socket.h>
#include <pipe/pipe.h>

using namespace std::chrono;

int main (int argc, char* argv []) {
    retcode_ sts;
    std::string method = argc > 1 ? std::string(argv[1]) : "boost_shm";
    size_d packetSize = argc > 2 ? std::stoi(argv[2]) : 100;
    int iteration = 1000000;

    std::cout << "---------------------------" << std::endl;
    std::cout << "METHOD: " << method << std::endl;
    std::cout << "POCKET SIZE:" << packetSize << std::endl;
    std::cout << "MESSAGE COUNT:" << iteration << std::endl;
    std::cout << "---------------------------" << std::endl;

    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "Process creation is failed!" << std::endl;
        return -1;
    } else if (pid != 0) { // Parent process (Server)
        char data[packetSize];
        std::unique_ptr<AbstractIPC> obj;
        if (method == "boost_shm") {
            obj = std::unique_ptr<AbstractIPC>(new BoostSharedMemory("phm_test", IPCMode::Server, packetSize));
        } else if (method == "named_pipe") {
            obj = std::unique_ptr<AbstractIPC>(new NamedPipe("phm_test", IPCMode::Server, packetSize));
        } else if (method == "domain_socket") {
            sleep(1);
            obj = std::unique_ptr<AbstractIPC>(new UnixDomainSocket("phm_test", IPCMode::Server, packetSize));
        }
        if ((sts = obj->initialize()) != SUCCESS_RET) {
            std::cerr << "SERVER: INITIALIZATION is failed" << std::endl;
            return sts;
        }

        long totalWriteDuration = 0;
        long minimumWriteDuration = 10000;
        long maximumWriteDuration = 0;

        for (int i = 0; i < iteration; i++) {
            auto start = high_resolution_clock::now();
            memset(&data, static_cast<char>(i + 100), packetSize);
            if (obj->update(&data) != SUCCESS_RET) {
                std::cout << "SERVER: " << "Error Updating" << std::endl;
            } /*else {
                std::cout << "SERVER: " << std::string(data) << std::endl;
            }*/
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            totalWriteDuration += duration.count();
            if (minimumWriteDuration > duration.count()) {
                minimumWriteDuration = duration.count();
            }
            if (maximumWriteDuration < duration.count()) {
                maximumWriteDuration = duration.count();
            }
//            sleep(0.1);
        }

        std::cout << "Total Write Duration: " << totalWriteDuration << " microseconds" << std::endl;
        std::cout << "Average Write Duration: " << (float) totalWriteDuration / (float) iteration << " microseconds" << std::endl;
        std::cout << "Minimum Write Duration: " << minimumWriteDuration << " microseconds" << std::endl;
        std::cout << "Maximum Write Duration: " << maximumWriteDuration << " microseconds" << std::endl;
        sleep(2);
        obj->terminate();
    } else { // Child process (Client)
        char data[packetSize];
        std::unique_ptr<AbstractIPC> obj;
        if (method == "boost_shm") {
            obj = std::unique_ptr<AbstractIPC>(new BoostSharedMemory("phm_test", IPCMode::Client, packetSize));
        } else if (method == "named_pipe") {
            obj = std::unique_ptr<AbstractIPC>(new NamedPipe("phm_test", IPCMode::Client, packetSize));
        } else if (method == "domain_socket") {
            obj = std::unique_ptr<AbstractIPC>(new UnixDomainSocket("phm_test", IPCMode::Client, packetSize));
        }
        if ((sts = obj->initialize()) != SUCCESS_RET) {
            std::cerr << "CLIENT: INITIALIZATION is failed" << std::endl;
            return sts;
        }

        long totalReadDuration = 0;
        long minimumReadDuration = 10000;
        long maximumReadDuration = 0;

        for (int i = 0; i < iteration; i++) {
            auto start = high_resolution_clock::now();
            if (obj->get(&data) != SUCCESS_RET) {
                std::cout << "CLIENT: " << "Error Getting" << std::endl;
            } /*else {
                std::cout << "CLIENT: " << std::string(data) << std::endl;
            }*/

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            totalReadDuration += duration.count();
            if (minimumReadDuration > duration.count()) {
                minimumReadDuration = duration.count();
            }
            if (maximumReadDuration < duration.count()) {
                maximumReadDuration = duration.count();
            }
//            sleep(1);
        }

        std::cout << "Total Read Duration: " << totalReadDuration << " microseconds" << std::endl;
        std::cout << "Average Read Duration: " << (float) totalReadDuration / (float) iteration << " microseconds" << std::endl;
        std::cout << "Minimum Read Duration: " << minimumReadDuration << " microseconds" << std::endl;
        std::cout << "Maximum Read Duration: " << maximumReadDuration << " microseconds" << std::endl;
        sleep(2);
        obj->terminate();
    }

    return 0;
}
