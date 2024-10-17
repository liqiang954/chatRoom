#pragma once

#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>
#include <exception>
#include <iostream>

namespace beast=boost::beast;
namespace net=boost::asio;
namespace http=beast::http;
using tcp=boost::asio::ip::tcp;