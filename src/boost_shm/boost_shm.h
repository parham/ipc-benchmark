
#ifndef IPC_BENCHMARK_BOOST_SHM_H
#define IPC_BENCHMARK_BOOST_SHM_H

#include <common/core.h>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

template <typename MessageType> class BoostSharedMemory : public AbstractIPC<MessageType> {
private:
    shared_memory_object * sharedMemory{};
    mapped_region * regionMemory{};

public:
    BoostSharedMemory(std::string title, IPCMode mode) :
        AbstractIPC<MessageType>(title, mode) {}
    ~BoostSharedMemory();

    _retcode initialize();
    _retcode terminate();
    _retcode update(const MessageType & data);
    _retcode get(MessageType & data);
};


#endif //IPC_BENCHMARK_BOOST_SHM_H
