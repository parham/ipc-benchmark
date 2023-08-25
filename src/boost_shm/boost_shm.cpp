
#include "boost_shm.h"

using namespace boost::interprocess;

BoostSharedMemory::~BoostSharedMemory() {
    if (this->getStatus()) {
        delete sharedMemory;
        delete regionMemory;
    }
}

retcode_ BoostSharedMemory::terminate() {
    if (!this->getStatus()) {
        return NOT_INITIALIZED;
    }
    this->setStatus(false);
    sharedMemory->remove(this->getName().c_str());

    return SUCCESS_RET;
}

retcode_ BoostSharedMemory::initialize() {
    if (this->getStatus()) {
        return ALREADY_INITIALIZED;
    }
    // Create a shared memory segment. Throws if already created
    if (this->getMode() == Server) {
        sharedMemory = new shared_memory_object(
            open_or_create,
            this->getName().c_str(), //name
            read_write
        );
        // Set the size of shared memory
        sharedMemory->truncate(containerSize);
        // Region for shared memory
        regionMemory = new mapped_region(
            sharedMemory,
            read_write
        );
    } else if (this->getMode() == Client) {
        sharedMemory = new shared_memory_object(
            open_only,  //open or create
            this->getName().c_str(), //name
            read_only
        );
        // Region for shared memory
        regionMemory = new mapped_region(
            sharedMemory,
            read_only
        );
    }

    // Set the status to alive
    this->setStatus(true);

    return SUCCESS_RET;
}

retcode_ BoostSharedMemory::update(DataPtr_ data) {
    if (!this->getStatus()) {
        return NOT_INITIALIZED;
    }
    if (this->getMode() != Server) {
        return NOT_ALLOWED;
    }
    // Copy the data to shared memory
    memcpy(regionMemory->get_address(), data, containerSize);
    return SUCCESS_RET;
}

retcode_ BoostSharedMemory::get(DataPtr_ data) {
    if (!this->getStatus()) {
        return NOT_INITIALIZED;
    }
    // Copy the data from shared memory
    memcpy(data, regionMemory->get_address(), containerSize);
    return SUCCESS_RET;
}