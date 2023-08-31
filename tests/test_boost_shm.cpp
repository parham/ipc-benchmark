
#include <memory>
#include <iostream>

#include <common/core.h>
#include <boost_shm/boost_shm.h>

int main (int argc, char* argv []) {
//    size_d packetSize = 100;
//    pid_t pid = fork();
//    if (pid == -1) {
//        std::cerr << "Process creation is failed!" << std::endl;
//        return -1;
//    } else if (pid != 0) { // Parent process (Server)
//        char data[packetSize];
//        BoostSharedMemory obj("phm_test", IPCMode::Server, packetSize);
//        obj.initialize();
//        for (int i = 0; i < 10; i++) {
//            memset(&data, static_cast<char>(i + 100), packetSize);
//            if (obj.update(&data) != SUCCESS_RET) {
//                std::cout << "SERVER: " << "Error Updating" << std::endl;
//            }
//            std::cout << "SERVER: " << std::string(data) << std::endl;
//            sleep(1);
//        }
//        obj.terminate();
//    } else { // Child process (Client)
//        char data[packetSize];
//        BoostSharedMemory obj("phm_test", IPCMode::Client, packetSize);
//        obj.initialize();
//        for (int i = 0; i < 10; i++) {
//            if (obj.get(&data) != SUCCESS_RET) {
//                std::cout << "CLIENT: " << "Error Getting" << std::endl;
//            }
//            std::cout << "CLIENT: " << std::string(data) << std::endl;
//            sleep(1);
//        }
//        obj.terminate();
//    }

    return 0;
}
