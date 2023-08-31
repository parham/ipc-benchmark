
#include "pipe.h"

retcode_ UnnamedPipe::initializeImpl_() {
    if (pipe(streamFD) < 0) {
        return PIPE_CREATION_FAILED;
    }
    if (this->getMode() == IPCMode::Server) {
        streamFILE = fdopen(streamFD[PIPE_SERVER], "w");
        if(streamFILE == nullptr) {
            return STREAM_CREATION_FAILED;
        }
    } else if (this->getMode() == IPCMode::Client) {
        streamFILE = fdopen(streamFD[PIPE_CLIENT], "r");
        if(streamFILE == nullptr) {
            return STREAM_CREATION_FAILED;
        }
    }

    return SUCCESS_RET;
}

retcode_ UnnamedPipe::terminateImpl_() {
    close(streamFD[PIPE_SERVER]);
    close(streamFD[PIPE_CLIENT]);
    return SUCCESS_RET;
}

retcode_ UnnamedPipe::updateImpl_(DataPtr_ data) {
    if (fwrite(data, containerSize, 1, streamFILE) == -1) {
        return WRITING_FAILED;
    }
    fflush(streamFILE);
    return SUCCESS_RET;
}

retcode_ UnnamedPipe::getImpl_(DataPtr_ data) {
    if (fread(data, containerSize, 1, streamFILE) == -1) {
        return READING_FAILED;
    }
    return SUCCESS_RET;
}