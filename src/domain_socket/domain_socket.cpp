
#include "domain_socket.h"

retcode_ UnixDomainSocket::initializeImpl_() {
    memset(&netAddress, 0, sizeof(netAddress));
    if (this->getMode() == IPCMode::Server) {
        netSocket = socket(AF_UNIX, SOCK_DGRAM, 0);
        if (netSocket < 0) {
            return SOCKET_CREATION_FAILED;
        }
        netAddress.sun_family = AF_UNIX;
        strcpy(netAddress.sun_path, this->getName().c_str());
    } else if (this->getMode() == IPCMode::Client) {
        netSocket = socket(AF_UNIX, SOCK_DGRAM, 0);
        if (netSocket < 0) {
            return SOCKET_CREATION_FAILED;
        }
        netAddress.sun_family = AF_UNIX;
        strcpy(netAddress.sun_path, this->getName().c_str());
        if (bind(netSocket, (sockaddr *) &netAddress, sizeof(netAddress))) {
            perror("binding name to datagram socket");
            exit(1);
        }
    }

    return SUCCESS_RET;
}

retcode_ UnixDomainSocket::terminateImpl_() {
    close(netSocket);
    return SUCCESS_RET;
}

retcode_ UnixDomainSocket::updateImpl_(DataPtr_ data) {
    socklen_t address_length = sizeof(netAddress.sun_family)+strlen(getName().c_str());
    sendto(netSocket, data, containerSize, MSG_CONFIRM, (struct sockaddr *) &netAddress, address_length);
    return SUCCESS_RET;
}

retcode_ UnixDomainSocket::getImpl_(DataPtr_ data) {
    socklen_t address_length = sizeof(netAddress.sun_family)+strlen(getName().c_str());
    recvfrom(netSocket, data, containerSize, MSG_WAITALL, (struct sockaddr *) &netAddress, &address_length);
    return SUCCESS_RET;
}