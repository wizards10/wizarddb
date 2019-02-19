#ifndef TCP_CONNECT
#define TCP_CONNECT
#include "data.hpp"
#include "core.hpp"
#include "pd.hpp"
#define TCPCONNECT_GETLASTERROR errno
#define DEFAULT_ADDRESSLEN INET_ADDRSTRLEN
class tcpConnect
{
public:
    tcpConnect(bool is_server);
    tcpConnect(){}
    ~tcpConnect();
public: 
    Buffer* in;
    Buffer* out;
    char peer_ip[DEFAULT_ADDRESSLEN];
    int peer_port;
    char local_ip[INET_ADDRSTRLEN];
    int local_port;
    static tcpConnect* connect(const char* ip , int port);
    static tcpConnect* bind_listen(const char* ip ,  int port);
    //buffer
    int flush();
    //Net
    void setNonblock();
    int setTcpSoLinger(int lOnOff , int linger);
    void isnoblock()const;
    int sockfd()const; 
    tcpConnect* accept();
    int read();
    int write();
    int clear();
    void close();
private:
    int sock;
    bool noblock;
    std::vector<Datas> datas;
    bool _init;
    struct sockaddr_in _localAddress;
    struct sockaddr_in _peerAddress;
    int _timeout_ms;
};
#endif