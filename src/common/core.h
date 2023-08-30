
#include<string>
#include <utility>

#ifndef PHM_BENCHMARK_CORE_H
#define PHM_BENCHMARK_CORE_H

#define SUCCESS_RET 0
#define ALREADY_INITIALIZED 1
#define NOT_INITIALIZED 2
#define NOT_ALLOWED 3
#define FIFO_CREATE_FAILED 4
#define WRITING_FAILED 5
#define READING_FAILED 6
#define SOCKET_CREATION_FAILED 7

typedef enum {
    Server,
    Client
} IPCMode;

typedef uint retcode_;
typedef void * DataPtr_;
typedef uint size_d;

class AbstractIPC {
private:
    bool status_;
    std::string name_;
    IPCMode mode_;
public:
    AbstractIPC(std::string title, IPCMode mode) :
        status_(false),
        name_(std::move(title)),
        mode_(mode){}
    ~AbstractIPC() = default;

    IPCMode getMode() {return mode_;}
    std::string getName() {return this->name_;}
    [[nodiscard]] bool getStatus() const {return this->status_;}
    void setStatus(bool status) {this->status_ = status;}

public:
    retcode_ initialize();
    retcode_ terminate();
    retcode_ update(DataPtr_ data);
    retcode_ get(DataPtr_ data);

protected:
    virtual retcode_ initializeImpl_() = 0;
    virtual retcode_ terminateImpl_() = 0;
    virtual retcode_ updateImpl_(DataPtr_ data) = 0;
    virtual retcode_ getImpl_(DataPtr_ data) = 0;
};

#endif //PHM_BENCHMARK_CORE_H
