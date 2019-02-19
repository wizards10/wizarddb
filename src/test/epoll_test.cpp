#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <map>
#include <string>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
struct msg
{
    int i ;
    char ip[1024*1024];
    char mac[1024];
    char h[12] ;
};
class socket_
{
public:
    socket_(int argc , char** argv)
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
    void epoll_test(char** argv)
    {
        int listenfd = socket(AF_INET , SOCK_STREAM , 0);
        port = atoi(argv[1]);
        memset(&addr , sizeof(addr) , 0);
        addr.sin_family = AF_INET;
        addr.sin_port = htons((short)port);
        addr.sin_addr.s_addr = INADDR_ANY;
        int r = ::bind(listenfd , (struct sockaddr*)&addr , sizeof(struct sockaddr));
        r = listen(listenfd , 20);
        setNonBlock(listenfd);
        int epollfd = epoll_create(20);
        updataEvents(epollfd,listenfd,EPOLLIN , EPOLL_CTL_ADD);
        printf("fd %d listening at %d\n",listenfd ,port);   
        for(;;)
        {
            loop_once(epollfd , listenfd , 1);
        }      
    }
    void setNonBlock(int fd)
    {
        int flags = fcntl(fd , F_GETFL , 0);
        int err = fcntl(fd , F_SETFL , flags | O_NONBLOCK);
    }
    void updataEvents (int efd , int fd , int events , int op)
    {
        struct epoll_event ev;
        memset(&ev , 0 , sizeof(ev));
        ev.events = events;//EPOLLIN ready read
        ev.data.fd = fd;
        int err = epoll_ctl(efd , op , fd ,&ev);
    }
    void loop_once(int efd , int lfd , int waitms)
    {
        cout<<"loop_once start"<<endl;
        const int MaxEvents = 20;
        struct epoll_event activeEvs[100];
        int n = epoll_wait(efd , activeEvs , MaxEvents , waitms);
        for(int i = 0 ; i < n ; i++)
        {
            int fd = activeEvs[i].data.fd;
            int events = activeEvs[i].events;
            if(events & ( EPOLLIN | EPOLLERR) )
            {
                if(fd == lfd)
                {
                    handleAccept(efd , fd);
                }
                else
                {
                    handleRead(efd , fd);
                }
            }
        }
    }
    void handleAccept(int efd , int fd)
    {
        struct sockaddr_in raddr;
        socklen_t rsz = sizeof(raddr);
        int cfd = accept(fd , (struct sockaddr*)&raddr , &rsz);
        sockaddr_in peer,local;
        socklen_t alen = sizeof(peer);
        int err = getpeername(cfd , (sockaddr*)&peer , &alen);
        setNonBlock(cfd);
        updataEvents(efd , cfd , EPOLLIN , EPOLL_CTL_ADD);
    }
    void handleRead(int efd , int fd)
    {
        char buf[1024*1024*2];
        int n = 0 ;
        int rc = 0;
        msg* Msg = new msg();
        memset(buf , 0 ,sizeof(buf));
        rc =  recv(&buf[0],sizeof(msg),fd);
        if(rc > 0)
        {
            memcpy(Msg , buf , sizeof(msg));
            cout<<"Msg data is "<<Msg->i<<endl;
            cout<<"Msg h  is "<<Msg->h<<endl;
        }
    }
    int recv(char *pMsg, int len , int _fd )
    {
        int rc = 0;
        while(len > 0)
        {
            cout<<"Start recv data"<<endl;
            rc = ::recv(_fd, pMsg, len,MSG_NOSIGNAL );
            if (rc > 0)
            {
                len -= rc;
                pMsg += rc;
            }
            else if(rc == 0)
            {
                close(_fd);
                cout<<"--------------------client have closed socket"<<endl;
                return rc;
            }
        }
        cout<<"This processor rc = "<<rc <<endl;
        return rc;
    }
    socket_()
    {}

private:
    int port;
    struct sockaddr_in addr;
};
int main(int argc ,char** argv)
{
    socket_ test;
    test.epoll_test(argv);
    return 0;
}
