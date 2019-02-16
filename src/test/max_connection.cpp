#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#define MAX_PORTS 1000
class test
{
public:
    test(int argc , char** argv)
    {
        port = atoi(argv[2]);
        const char* ip = argv[1];
        memset(&addr , sizeof(addr), 0);
        addr.sin_family = AF_INET;
        inet_pton(AF_INET , ip , &addr.sin_addr);
        addr.sin_port = htons((short)port);
    }
    void Accept_Block()
    {
        struct linger ling;
        int sock;
        sock = socket(AF_INET,SOCK_STREAM,0);
        connect(sock,(struct sockaddr*)&addr , sizeof(addr));
        ling.l_onoff = 1; //cause RST to be sent on close()
        ling.l_linger = 0;
        setsockopt(sock , SOL_SOCKET , SO_LINGER , &ling , sizeof(ling));
        close(sock);
        sleep(2);
        return;
    }
private:
    int port;
    struct sockaddr_in addr;
};
int main(int argc ,char** argv)
{
    test a(argc , argv);
    a.Accept_Block();
    return 0;
}