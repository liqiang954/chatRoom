#pragma once

#include "const.h"

class LogicSystem;
class HttpConnection:public std::enable_shared_from_this<HttpConnection>
{
    friend class LogicSystem;
private:
tcp::socket _socket;
beast::flat_buffer _buffer{8192};
http::request<http::dynamic_body> _request;
http::response<http::dynamic_body> _response;
net::steady_timer _deadline{_socket.get_executor(),std::chrono::seconds(60)};


void checkdeadline();
void writeResponse();
void handleReq();

public:
HttpConnection(tcp::socket socket);
void start();


};

