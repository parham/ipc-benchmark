
#include "domain_socket.h"

retcode_ UnixDomainSocket::initializeImpl_() {
    memset(&netAddress, 0, sizeof(netAddress));
    netSocket = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (netSocket == -1) {
        return SOCKET_CREATION_FAILED;
    }
    netAddress.sun_family = AF_UNIX;
    strcpy(netAddress.sun_path, this->getName().c_str());

    return SUCCESS_RET;
}

retcode_ UnixDomainSocket::terminateImpl_() {
    close(netSocket);
    return SUCCESS_RET;
}

retcode_ UnixDomainSocket::updateImpl_(DataPtr_ data) {
    sendto(netSocket, data, containerSize, MSG_CONFIRM, &netAddress, sizeof(netAddress));
    return SUCCESS_RET;
}

retcode_ UnixDomainSocket::getImpl_(DataPtr_ data) {
    recvfrom(netSocket, data, containerSize, MSG_WAITALL, &netAddress, sizeof(netAddress));
    return SUCCESS_RET;
}