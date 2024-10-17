#include "httpconnection.h"
#include "LogicSystem.h"

void HttpConnection::checkdeadline()
{
    auto self=shared_from_this();
    _deadline.async_wait([self](beast::error_code ec){
        if(!ec)
        {
            self->_socket.close();
        }
    });

}

void HttpConnection::writeResponse()
{
    //callback
    auto self=shared_from_this();
    _response.content_length(_response.body().size());
    http::async_write(
        _socket,_response,[self](beast::error_code ec,std::size_t size){
            self->_socket.shutdown(tcp::socket::shutdown_send,ec);
            self->_deadline.cancel();
        }
    );
}

void HttpConnection::handleReq()
{
    _response.version(_request.version());
    _response.keep_alive(false);
    if(_request.method()==http::verb::get)
    {
        //逻辑回调
        bool success=LogicSystem::instance().handleGet(_request.target().to_string(),shared_from_this());
        if(!success)
        {
            _response.result(http::status::not_found);
            _response.set(http::field::content_type,"text/plain");
            beast::ostream(_response.body())<<"url not found 1\r\n";
            writeResponse();
            return;
        }
         _response.result(http::status::ok);
         _response.set(http::field::server,"GatServer");
         writeResponse();
         return;

    }

}

HttpConnection::HttpConnection(tcp::socket socket) : _socket(std::move(socket))
{


}

void HttpConnection::start()
{
    auto self=shared_from_this();
    http::async_read(_socket,_buffer,_request,[self](beast::error_code ec,std::size_t bytes_transferred){
        try
        {
            if(ec)
            {
                std::cout<<"http read error: "<<ec.what()<<'\n';
                return;
            }

            boost::ignore_unused(bytes_transferred);
            self->handleReq();
            self->checkdeadline();

        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    });

}
