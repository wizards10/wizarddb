#include "core.hpp"
#include "osssocket.hpp"
#include "pmdTcpListener.hpp"
#define PMD_TCPLISTENER_RETRY 5
#define OSS_MAX_SERVICENAME NI_MAXSERV

int pmdTcpListenerEntryPoint()
{
    int rc = EDB_OK;
    int port = 2333;
    _ossSocket sock(port);
    rc = sock.initSocket();
    if(rc)
    {
        printf("Failed to initialize socket , rc = %d " , rc);
        goto error;
    }
    rc = sock.bind_listen();
    if(rc)
    {
        printf("Failed to bind or listen socket , rc = %d " , rc);
        goto error;
    }
    while(true)
    {
        int s;
        rc = sock.accept(&s , NULL , NULL );
        if( rc == EDB_TIMEOUT )
        {
            rc = EDB_OK;
            continue;
        }
        char buffer[1024];
        int size;
        _ossSocket sock1(&s);
        sock1.disableNagle();
        do
        {
            rc = sock1.recv((char*)&size , 4);
            if( rc && rc != EDB_TIMEOUT )
            {
                printf("Failed to receive size , rc = %d " , rc);
                goto error;
            }
        }
        while(EDB_TIMEOUT == rc);
        do
        {
            rc = sock1.recv(&buffer[0] , size - sizeof(int));
            if(rc && rc != EDB_TIMEOUT)
            {
                printf("Failed to receive buffer , rc = %d " , rc );
                goto error;
            }
        }
        while( EDB_TIMEOUT == rc) ; 
        printf("%s\n " , buffer);
        sock1.close();
    }
    done:
    return rc;
    error:
    switch(rc)
    {
        case EDB_SYS:
        {
            printf("System error occured ");
            break;
        }
        default :
        {
            printf("Internal error");
        }
        goto done;
    }

}