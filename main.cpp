
#include <iostream>

#include <boost_shm/boost_shm.h>

typedef struct {
    int length;
    int data;
} MemoryObject;

int main (int argc, char* argv []) {
    if (argc == 1) {
        std::cout << "Server side Process" << std::endl;
        BoostSharedMemory<MemoryObject> obj("phm_test", IPCMode::Server);
        if (obj.initialize() == SUCCESS_RET) {
            std::cout << "Server is initialized!" << std::endl;
        }
        MemoryObject data {100, 0};
        for (int i = 0; i < 100; i++) {
            data.data = i;
            if (obj.update(data) != SUCCESS_RET) {
                std::cout << "Server is failed to update data!" << std::endl;
                return -1;
            }
        }
        obj.terminate();
    } else {
        std::cout << "Client side Process" << std::endl;
        BoostSharedMemory<MemoryObject> obj("phm_test", IPCMode::Client);
        if (obj.initialize() == SUCCESS_RET) {
            std::cout << "Server is initialized!" << std::endl;
        }
        MemoryObject data {1, 0};
        for (int i = 0; i < 100; i++) {
            if (obj.get(data) != SUCCESS_RET) {
                std::cout << "Client is failed to update data!" << std::endl;
                return -1;
            }
        }
        obj.terminate();
    }

    return 0;
}
