#include "const.h"
#include <vector>
#include "cserver.h"


int main() {
   

try
{
    /* code */
    unsigned short int port=8080;
    net::io_context ioc{1};
    boost::asio::signal_set signals(ioc,SIGINT,SIGTERM);
    signals.async_wait([&ioc](const boost::system::error_code& ec,int single_num){
        if(ec)
        {
            return;

        }
        ioc.stop();
    });
    std::make_shared<CServer>(ioc,port)->start();
    ioc.run();

}
catch(const std::exception& e)
{
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
}



    return 0;
}