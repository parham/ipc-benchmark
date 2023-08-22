
#include "boost_shm.h"

template <typename MessageType> BoostSharedMemory<MessageType>::~BoostSharedMemory() {
    if (this->getStatus()) {
        delete sharedMemory;
        delete regionMemory;
    }
}

template <typename MessageType> _retcode BoostSharedMemory<MessageType>::terminate() {
    if (!this->getStatus()) {
        return NOT_INITIALIZED;
    }
    this->setStatus(false);
    sharedMemory->remove(this->getName());

    return SUCCESS_RET;
}

template <typename MessageType> _retcode BoostSharedMemory<MessageType>::initialize() {
    if (this->getStatus()) {
        return ALREADY_INITIALIZED;
    }
    // Create a shared memory segment. Throws if already created
    if (this->getMode() == Server) {
        sharedMemory = new shared_memory_object(
            open_or_create,
            this->getName(), //name
            read_write
        );
        // Set the size of shared memory
        sharedMemory->truncate(sizeof(MessageType));
        // Region for shared memory
        regionMemory = new mapped_region(
            sharedMemory,
            read_write
        );
    } else if (this->getMode() == Client) {
        sharedMemory = new shared_memory_object(
            open_only,  //open or create
            this->getName(), //name
            open_read_only
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

template <typename MessageType> _retcode BoostSharedMemory<MessageType>::update(const MessageType & data) {
    if (!this->getStatus()) {
        return NOT_INITIALIZED;
    }
    if (this->getMode() != Server) {
        return NOT_ALLOWED;
    }
    // Copy the data to shared memory
    memcpy(regionMemory->get_address(), &data, sizeof(MessageType));
    return SUCCESS_RET;
}

template <typename MessageType> _retcode BoostSharedMemory<MessageType>::get(MessageType & data) {
    if (!this->getStatus()) {
        return NOT_INITIALIZED;
    }
    // Copy the data from shared memory
    memcpy(&data, regionMemory->get_address(), sizeof(MessageType));
    return SUCCESS_RET;
}