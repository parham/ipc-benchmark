
#include <memory>
#include <iostream>

#include <common/core.h>
#include <boost_shm/boost_shm.h>
#include <named_pipe/named_pipe.h>
#include <domain_socket/domain_socket.h>

int main (int argc, char* argv []) {
    retcode_ sts;
    size_d packetSize = 100;
    std::string method;
    method = argc == 1 ? "boost_shm" : std::string(argv[1]);

    std::cout << "METHOD: " << method << std::endl;

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
            obj = std::unique_ptr<AbstractIPC>(new UnixDomainSocket("phm_test", IPCMode::Server, packetSize));
        }
        if ((sts = obj->initialize()) != SUCCESS_RET) {
            std::cerr << "SERVER: INITIALIZATION is failed" << std::endl;
            return sts;
        }
        for (int i = 0; i < 10; i++) {
            memset(&data, static_cast<char>(i + 100), packetSize);
            if (obj->update(&data) != SUCCESS_RET) {
                std::cout << "SERVER: " << "Error Updating" << std::endl;
            } else {
                std::cout << "SERVER: " << std::string(data) << std::endl;
            }
            sleep(1);
        }
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
        for (int i = 0; i < 10; i++) {
            if (obj->get(&data) != SUCCESS_RET) {
                std::cout << "CLIENT: " << "Error Getting" << std::endl;
            } else {
                std::cout << "CLIENT: " << std::string(data) << std::endl;
            }
            sleep(1);
        }
        obj->terminate();
    }

    return 0;
}
