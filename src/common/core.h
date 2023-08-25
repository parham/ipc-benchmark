
#include<string>
#include <utility>

#ifndef PHM_BENCHMARK_CORE_H
#define PHM_BENCHMARK_CORE_H

#define SUCCESS_RET 0
#define ALREADY_INITIALIZED 1
#define NOT_INITIALIZED 2
#define NOT_ALLOWED 3

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
    virtual retcode_ initialize() = 0;
    virtual retcode_ terminate() = 0;
    virtual retcode_ update(DataPtr_ data) = 0;
    virtual retcode_ get(DataPtr_ data) = 0;
};

#endif //PHM_BENCHMARK_CORE_H
