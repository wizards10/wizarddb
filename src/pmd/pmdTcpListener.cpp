#include "core.hpp"
#include "pmdTcpListener.hpp"
#include "tcpConnect.hpp"
class tcpConnect;
int pmdTcpListenerEntryPoint()
{
    int rc = EDB_OK;
    int port = 2333;
    char ip[] = "192.168.114.129";
    tcpConnect* serv = tcpConnect::bind_listen(ip , port);
    tcpConnect* client = serv->accept();
    printf("%s\n",client->peer_ip);
    std::cout<<"client port = "<<client->peer_port<<std::endl;
}