
#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace shm_boost = boost::interprocess;

typedef struct {
    int length;
    char data[100];
} MemoryObject;

int main (int argc, char* argv []) {
    if (argc == 1) {
        std::cout << "Server side Process" << std::endl;
        // Create a shared memory segment. Throws if already created
        shm_boost::shared_memory_object shm_obj (
                shm_boost::open_or_create,  //open or create
                "phm_shm", //name
                shm_boost::read_write  //read-only mode
        );
        // Set the size of shared memory
        shm_obj.truncate(10000);

        MemoryObject obj;
        obj.length = 100 * sizeof(char);

        // Region for shared memory
        shm_boost::mapped_region region(shm_obj, shm_boost::read_write);

        for (int i = 0; i < 100; i++) {
            memset(&obj.data, 30 + i, obj.length);
            memcpy(region.get_address(), &obj, sizeof(obj));
            std::cout << (int) obj.data[20] << std::endl;
            sleep(2);
        }
        std::cout << "Server is terminated!" << std::endl;
        shm_obj.remove("phm_shm");
    } else {
        std::cout << "Client side Process" << std::endl;
        shm_boost::shared_memory_object shm_obj (
                shm_boost::open_only,  //open or create
                "phm_shm", //name
                shm_boost::read_only  //read-only mode
        );
        shm_boost::mapped_region region(shm_obj, shm_boost::read_only);
        MemoryObject obj;
        for (int i = 0; i < 100; i++) {
            memcpy(&obj, region.get_address(), sizeof(obj));
            std::cout << (int) obj.data[20] << std::endl;
            sleep(1);
        }
    }

    return 0;
}
