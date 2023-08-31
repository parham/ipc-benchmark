//
// Created by phm on 30/08/23.
//

#ifndef IPC_BENCHMARK_PIPE_H
#define IPC_BENCHMARK_PIPE_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <common/core.h>

#define PIPE_SERVER 1
#define PIPE_CLIENT 0

class UnnamedPipe : public AbstractIPC {
private:
    size_d containerSize;
    int streamFD[2];
    FILE * streamFILE{};

public:
    UnnamedPipe(std::string name, IPCMode mode, size_d csize) : AbstractIPC(std::move(name), mode), containerSize(csize) {}

protected:
    retcode_ initializeImpl_() override;
    retcode_ terminateImpl_() override;
    retcode_ updateImpl_(DataPtr_ data) override;
    retcode_ getImpl_(DataPtr_ data) override;
};

#endif //IPC_BENCHMARK_PIPE_H
