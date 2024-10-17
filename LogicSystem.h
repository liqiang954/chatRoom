#pragma once

#include "const.h"
#include <map>
#include <functional>


class HttpConnection;
template<typename T>
class Singleton
{
public:
    static T& instance()
    {
        static T _instance;
        return _instance;

    }
protected:
    Singleton()=default;
    ~Singleton()=default;
    Singleton(Singleton&)=delete;
    Singleton& operator=(Singleton&)=delete;


};

typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandle;
class LogicSystem:public Singleton<LogicSystem>,public std::enable_shared_from_this<LogicSystem>
{
    friend class Singleton<LogicSystem>;
    //friend class HttpConnection;
private:
    /* data */
    std::map<std::string,HttpHandle> post_handle;
    std::map<std::string,HttpHandle> get_handle;

    LogicSystem(/* args */);

public:    
    ~LogicSystem();
    void reg_get(std::string,HttpHandle);
    bool handleGet(std::string ,std::shared_ptr<HttpConnection>);
};


