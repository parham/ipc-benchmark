
#include <iostream>

#include <common/core.h>
#include <boost_shm/boost_shm.h>

int main (int argc, char* argv []) {
    size_d packetSize = 100;
    if (argc == 1) {
        char data[packetSize];

        BoostSharedMemory obj("phm_test", IPCMode::Server, packetSize);
        obj.initialize();
        for (int i = 0; i < 100; i++) {
            memset(&data, static_cast<char>(i + 100), packetSize);
            if (obj.update(&data) != SUCCESS_RET) {
                std::cout << "Error Updating" << std::endl;
            }
            std::cout << std::string(data) << std::endl;
            sleep(1);
        }
        obj.terminate();
    } else {
        char data[packetSize];
        BoostSharedMemory obj("phm_test", IPCMode::Client, packetSize);
        obj.initialize();
        for (int i = 0; i < 100; i++) {
            if (obj.get(&data) != SUCCESS_RET) {
                std::cout << "Error Getting" << std::endl;
            }
            std::cout << std::string(data) << std::endl;
            sleep(1);
        }
        obj.terminate();
    }

    return 0;
}
