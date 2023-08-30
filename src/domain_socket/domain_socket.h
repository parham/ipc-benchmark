
#ifndef IPC_BENCHMARK_DOMAIN_SOCKET_H
#define IPC_BENCHMARK_DOMAIN_SOCKET_H

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <common/core.h>

class UnixDomainSocket : public AbstractIPC {
private:
    size_d containerSize;
    sockaddr_un netAddress{};
    int netSocket{};

public:
    UnixDomainSocket(std::string name, IPCMode mode, size_d csize) : AbstractIPC(std::move(name), mode), containerSize(csize) {}

protected:
    retcode_ initializeImpl_() override;
    retcode_ terminateImpl_() override;
    retcode_ updateImpl_(DataPtr_ data) override;
    retcode_ getImpl_(DataPtr_ data) override;
};

#endif //IPC_BENCHMARK_DOMAIN_SOCKET_H
