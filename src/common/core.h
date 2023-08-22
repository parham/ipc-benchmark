
#include<string>
#include <utility>

#ifndef PHM_BENCHMARK_CORE_H
#define PHM_BENCHMARK_CORE_H

#define SUCCESS_RET 0
#define ALREADY_INITIALIZED 1
#define NOT_INITIALIZED 2
#define NOT_ALLOWED 3

typedef uint _retcode;

typedef enum {
    Server,
    Client
} IPCMode;

template <typename MessageType> class AbstractIPC {
private:
    bool status_;
    std::string name_;
    IPCMode mode_;
public:
    AbstractIPC(std::string title, IPCMode mode) :
        status_(false),
        name_(std::move(title)),
        mode_(mode){}
    ~AbstractIPC();

    IPCMode getMode() {return mode_;}
    std::string getName() {return this->name_;}
    bool getStatus() {return this->status_;}
    void setStatus(bool status) {this->status_ = status;}


    virtual _retcode initialize() = 0;
    virtual _retcode terminate() = 0;
    virtual _retcode update(const MessageType & data) = 0;
    virtual _retcode get(MessageType & data) = 0;
};

#endif //PHM_BENCHMARK_CORE_H
