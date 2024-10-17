#include "cserver.h"



CServer::CServer(net::io_context& ioc,unsigned short int port):_ioc(ioc),
 _acceptor(ioc,tcp::endpoint(tcp::v4(),port)),_socket(ioc)
 {

 }

 CServer::~CServer()
 {
 }

void CServer::start()
{
    try
    {
    auto self=shared_from_this();
    _acceptor.async_accept(_socket,[self](beast::error_code ec){
        if(ec)
        {
            self->start();
            return;


        }
        //处理新链接
        std::make_shared<HttpConnection>(std::move(self->_socket))->start();
        self->start();
        return;

    });

    }
    catch(std::exception& e){
        std::cout<<"exception is: "<<e.what()<<std::endl;

    }

}
