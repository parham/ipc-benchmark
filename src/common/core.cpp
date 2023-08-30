
#include "core.h"

retcode_ AbstractIPC::initialize() {
    if (this->getStatus()) {
        return ALREADY_INITIALIZED;
    }
    retcode_ sts = initializeImpl_();
    // Set the status to alive
    if (sts == SUCCESS_RET)
        this->setStatus(true);
    return sts;
}

retcode_ AbstractIPC::terminate() {
    if (!this->getStatus()) {
        return NOT_INITIALIZED;
    }
    this->setStatus(false);
    return terminateImpl_();
}

retcode_ AbstractIPC::update(DataPtr_ data) {
    if (!this->getStatus()) {
        return NOT_INITIALIZED;
    }
    if (this->getMode() != Server) {
        return NOT_ALLOWED;
    }
    return updateImpl_(data);
}

retcode_ AbstractIPC::get(DataPtr_ data) {
    if (!this->getStatus()) {
        return NOT_INITIALIZED;
    }
    return getImpl_(data);
}

