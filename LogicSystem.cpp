#include "LogicSystem.h"
#include "httpconnection.h"

LogicSystem::LogicSystem()
{
    reg_get("/get_test",[](std::shared_ptr<HttpConnection> connectionPtr){
        beast::ostream(connectionPtr->_response.body())<<"receive get_test req";

    });
}

LogicSystem::~LogicSystem()
{
}

void LogicSystem::reg_get(std::string url, HttpHandle handle)
{
    get_handle.insert(std::make_pair(url,handle));
}

bool LogicSystem::handleGet(std::string path, std::shared_ptr<HttpConnection> httpconnectionPtr)
{
    if(get_handle.find(path)==get_handle.end())
    {
        return false;

    }
    get_handle[path](httpconnectionPtr);
    return true;
}
