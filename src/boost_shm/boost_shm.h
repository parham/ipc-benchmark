
#ifndef IPC_BENCHMARK_BOOST_SHM_H
#define IPC_BENCHMARK_BOOST_SHM_H

#include <common/core.h>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <utility>

namespace shm_boost = boost::interprocess;

class BoostSharedMemory : public AbstractIPC {
private:
    size_d containerSize;
    shm_boost::shared_memory_object * sharedMemory{};
    shm_boost::mapped_region * regionMemory{};

public:
    BoostSharedMemory(std::string title, IPCMode mode, size_d csize) : AbstractIPC(std::move(title), mode), containerSize(csize) {}
    ~BoostSharedMemory();

protected:
    retcode_ initializeImpl_() override;
    retcode_ terminateImpl_() override;
    retcode_ updateImpl_(DataPtr_ data) override;
    retcode_ getImpl_(DataPtr_ data) override;
};

#endif //IPC_BENCHMARK_BOOST_SHM_H
