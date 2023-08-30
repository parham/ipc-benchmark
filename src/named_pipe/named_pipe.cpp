
#include "named_pipe.h"

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

retcode_ NamedPipe::initializeImpl_() {
    if (this->getMode() == Server) {
        int fid = mkfifo(pipPath.c_str(), 0666);
        if (fid < 0) {
            return FIFO_CREATE_FAILED;
        }
    }

    this->pipFID = open(this->pipPath.c_str(), this->getMode() == IPCMode::Server ? O_WRONLY : O_RDONLY);
    return SUCCESS_RET;
}

retcode_ NamedPipe::terminateImpl_() {
    close(this->pipFID);
    if (this->getMode() == Server) {
        remove(pipPath.c_str());
    }
    return SUCCESS_RET;
}

retcode_ NamedPipe::updateImpl_(DataPtr_ data) {
    int ret = write(this->pipFID, data, this->containerSize);
    if (ret < 0) {
        return WRITING_FAILED;
    }
    return SUCCESS_RET;
}

retcode_ NamedPipe::getImpl_(DataPtr_ data) {
    int ret = read(this->pipFID, data, this->containerSize);
    if (ret < 0) {
        return READING_FAILED;
    }
    return SUCCESS_RET;
}
