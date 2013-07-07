#ifndef __SOCKET__H_
#define __SOCKET__H_

#include <iostream>
#include <string>

#include "SocketException.h"

#ifdef __unix__
#   include <sys/types.h>
#   include <sys/socket.h>
#   include <sys/un.h>
#   include <netinet/in.h>
#   include <netdb.h>
#   include <arpa/inet.h>
#else
#   include <windows.h>
#   include <winsock.h>
#endif

typedef int SocketProtocol;

class Socket
{
public:
    enum SocketMode
    {
        UNINITIALIZED,
        TCPUNINITIALIZED,
        TCPCLIENT,
        TCPSERVER,
        UDPUNINITIALIZED,
        UDPCLIENT,
        UDPSERVER
    };
protected:
    int             m_SocketDescriptor;

    unsigned int    m_IPAddress;
    int             m_PortNumber;
    int             m_ErrorFlag;
    int             m_Mode;

    std::string     m_ErrorString;

private:
    bool            SocketInit();

public:
    Socket();
    Socket(SocketProtocol Protocol);
    virtual ~Socket();

    virtual int     GetError() const;
    virtual bool    Close() = 0;


    static SocketProtocol GetSocketProtocol(const char* ProtocolName);
};

#endif//__SOCKET__H_
