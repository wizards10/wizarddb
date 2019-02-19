#include "tcpConnect.hpp"

tcpConnect* tcpConnect::connect(const char* hostname , int port)
{
    tcpConnect* tcpLink;
    struct hostent* hp;
    struct sockaddr_in peerAddress;
    memset(&peerAddress, 0 , sizeof(sockaddr_in));
    if((hp = gethostbyname(hostname)))
    {
        peerAddress.sin_addr.s_addr = *((int*)hp->h_addr_list[0]);
    }
    else
    {
        peerAddress.sin_addr.s_addr = inet_addr(hostname); //Ipv4 address convert to string
    }
    peerAddress.sin_port = htons((short)port); //return net bytes
    //create local socket
    int rc = 0 ;
    int sock = -1;
    rc = sock = ::socket(AF_INET , SOCK_STREAM ,0);
    if(rc == -1)
    {
        PD_LOG(PDERROR,"Cannot create socket rc = %d" , rc);
        goto error;
    }
    rc = ::connect(sock, (struct sockaddr*)&peerAddress , sizeof(sockaddr));
    tcpLink = new tcpConnect();
    tcpLink->sock = sock;
done:
    return tcpLink;
error:
    goto done;
}
tcpConnect* tcpConnect::bind_listen(const char* ip , int port)
{
    tcpConnect* tcplink ;
    int sock = -1;
    int rc = 0; 
    struct sockaddr_in addr;
    memset(&addr , 0 , sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(short(port));
    inet_pton(AF_INET , ip , &addr.sin_addr);
    int temp = 1;
    bool is_server = true;
    rc = sock = ::socket(AF_INET , SOCK_STREAM , 0);
    if(rc < 0)
    {
        PD_LOG(PDERROR,"Cannot create socket rc = %d",rc);
        goto error;
    }
    rc = setsockopt(sock , SOL_SOCKET,SO_REUSEADDR,(char*)&temp , sizeof(int));
    if(rc < 0)
    {
        PD_LOG(PDERROR ,"Can not set So_reuseaddr rc = %d",rc);
        goto error;
    }
    rc = ::bind(sock , (struct sockaddr*)&addr,sizeof(sockaddr));
    if(rc < 0)
    {
        PD_LOG(PDERROR,"Can not bind socket rc = %d " , rc);
        goto error;
    }
    rc = ::listen(sock ,1024);
    if(rc < 0)
    {
        goto error;
    }
    tcplink  = new tcpConnect();
    tcplink->sock = sock;
done:
    return tcplink;
error:
    goto done;
}
tcpConnect* tcpConnect::accept()
{
    tcpConnect* tcplink;
    int client_sockfd;
    int rc;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    while(true)
    {
        rc = client_sockfd = ::accept(sock,(struct sockaddr*)&addr,&addrlen);
        if(rc < 0)
        {
            rc = errno;
            if(EINTR == rc)
            {
                continue;
            }
            break;
        }
        break;
    }
    tcplink = new tcpConnect();
    tcplink->sock = client_sockfd;
    inet_ntop(AF_INET , &addr , tcplink->peer_ip , sizeof(tcplink->peer_ip));
    inet_ntop(AF_INET , &addr.sin_addr , tcplink->peer_ip , sizeof(tcplink->peer_ip));
    tcplink->peer_port = ntohs(addr.sin_port);
    tcplink->setTcpSoLinger(1,0);
    return tcplink;
}
int tcpConnect::read()
{
    int rc = EDB_OK;
    int re;
    while((re = in->spaceBufSize()) > 0)
    {
        int len = ::read(sock , in->pointer() , re);
        if(len < 0)
        {
            rc = errno;
            if(rc == EINTR)
            {
                continue;
            }
            else if(rc == EWOULDBLOCK )
            {
                break;
            }
        }
        else
        {
            if(len == 0)
            {
                rc = 0 ;
                goto done;
            }
            rc+=len;
            in->incre(len);
        }  
    }
done:
    return rc;
error:
    goto done;
}
int tcpConnect::write()
{
    int rc = 0 ;
    int wr;
    while((wr = out->spaceBufSize()) > 0)
    {
        int len = ::write(sock , out->getdata() , wr);
        if(len == -1)
        {
            if(errno == EINTR)
            {
                continue;
            }
            else if(errno == EWOULDBLOCK)
            {
                break;
            }
        }
        else
        {
            if(len == 0)
            {
                goto error;
            }
            wr += len;
            out->decre(len);
        }
    }
done:
    return wr;
error:
    goto done ;
}
int tcpConnect::flush()
{
    int len = 0 ;
    while(!out->empty())
    {
        int ret = this->write();
        if(ret == -1)
        {
            return ret;
        }
        len+=ret;
    }
    return len;
}

tcpConnect::tcpConnect(bool is_server)
{
    if(true == is_server)
    {
        in = NULL;
        out = NULL;
    }
    else
    {
        in = new Buffer(DEFAULT_BUFFER_SIZE);
        out = new Buffer(DEFAULT_BUFFER_SIZE);
    }  
}
int tcpConnect::setTcpSoLinger(int lOnOff , int linger)
{
    int rc = EDB_OK;
    struct linger _linger;
    _linger.l_onoff = lOnOff;
    _linger.l_linger = linger;
    rc = setsockopt(sock, SOL_SOCKET,SO_LINGER,(const char*)&_linger,sizeof(_linger));
    return rc;
}
