#ifndef CSERVER_H
#define CSERVER_H

#include "const.h"
#include "httpconnection.h"


class CServer:public std::enable_shared_from_this<CServer>
{
private:
    /* data */
    net::io_context& _ioc;
    tcp::acceptor _acceptor;
    tcp::socket _socket;

public:
    CServer(net::io_context& ioc,unsigned short int port);
    ~CServer();

    void start();
};

 
#endif