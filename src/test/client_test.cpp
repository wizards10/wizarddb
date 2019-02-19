#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <string>
#include <iostream>
using namespace std;
#define MAX_PORTS 1000
struct msg
{
    int i ;
    char ip[1024*1024];
    char mac[1024];
    char h[12] ;
};
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
    void test1()
    {
        char send_buf[1024*1024*2];
        int sock;
        sock = socket(AF_INET,SOCK_STREAM,0);
        connect(sock,(struct sockaddr*)&addr , sizeof(addr));
        loop_send(sock);
        return;
    }
    int send(int fd , char* Msg , int len , int flags)
    {
        int rc = 0;
        cout<<"Msg data is"<<((msg*)Msg)->h<<endl;
        while(len > 0)
        {
            rc = ::send(fd,Msg,len,MSG_NOSIGNAL | flags);
            len -=rc;
            Msg += rc;
        }
        return rc;
    }
    void loop_send(int sock)
    {
        while(true)
        {
            msg* Msg = new msg();
            Msg->i = 777;
            memcpy(Msg->h , "clearlove" , 10);
            int len = sizeof(msg);
            int rc = send(sock , (char*)Msg, len , 0);
            delete Msg;
        }
        return;
    }
private:
    int port;
    struct sockaddr_in addr;
};
int main(int argc , char** argv)
{
    test a(argc , argv);
    a.test1();
    return 0;
}