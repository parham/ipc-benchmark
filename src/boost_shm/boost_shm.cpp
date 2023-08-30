
#include "boost_shm.h"

BoostSharedMemory::~BoostSharedMemory() {
    if (this->getStatus()) {
        delete sharedMemory;
        delete regionMemory;
    }
}

retcode_ BoostSharedMemory::terminateImpl_() {
    sharedMemory->remove(this->getName().c_str());
    return SUCCESS_RET;
}

retcode_ BoostSharedMemory::initializeImpl_() {
    // Create a shared memory segment. Throws if already created
    if (this->getMode() == Server) {
        sharedMemory = new shm_boost::shared_memory_object(
            shm_boost::open_or_create,
            this->getName().c_str(), //name
            shm_boost::read_write
        );
        // Set the size of shared memory
        sharedMemory->truncate(containerSize);
        // Region for shared memory
        regionMemory = new shm_boost::mapped_region(
            *sharedMemory,
            shm_boost::read_write
        );
    } else if (this->getMode() == Client) {
        sharedMemory = new shm_boost::shared_memory_object(
            shm_boost::open_only,  //open or create
            this->getName().c_str(), //name
            shm_boost::read_only
        );
        // Region for shared memory
        regionMemory = new shm_boost::mapped_region(
            *sharedMemory,
            shm_boost::read_only
        );
    }

    return SUCCESS_RET;
}

retcode_ BoostSharedMemory::updateImpl_(DataPtr_ data) {
    // Copy the data to shared memory
    memcpy(regionMemory->get_address(), data, containerSize);
    return SUCCESS_RET;
}

retcode_ BoostSharedMemory::getImpl_(DataPtr_ data) {
    // Copy the data from shared memory
    memcpy(data, regionMemory->get_address(), containerSize);
    return SUCCESS_RET;
}