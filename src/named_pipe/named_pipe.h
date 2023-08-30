//
// Created by phm on 25/08/23.
//

#ifndef IPC_BENCHMARK_NAMED_PIPE_H
#define IPC_BENCHMARK_NAMED_PIPE_H

#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>

#include <common/core.h>

namespace fs = std::filesystem;

class NamedPipe : public AbstractIPC {
private:
    size_d containerSize;
    fs::path pipPath;
    int pipFID{};

public:
    NamedPipe(std::string name, IPCMode mode, size_d csize) : AbstractIPC(std::move(name), mode), containerSize(csize) {
        fs::path dir (NAMED_PIPE_DIR);
        fs::path file (this->getName());
        this->pipPath = dir / file;
    }

protected:
    retcode_ initializeImpl_() override;
    retcode_ terminateImpl_() override;
    retcode_ updateImpl_(DataPtr_ data) override;
    retcode_ getImpl_(DataPtr_ data) override;
};

#endif //IPC_BENCHMARK_NAMED_PIPE_H
