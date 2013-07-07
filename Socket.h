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
typedef int SocketMode;
typedef int IPVersion;
class Socket
{
public:
    enum SocketModes
    {
        UNINITIALIZED,
        TCP = SOCK_STREAM,
        UDP = SOCK_DGRAM,
        RAW = SOCK_RAW
    };
    enum SocketDomains
    {
        IPv4 = AF_INET,
        IPv6 = AF_INET6
    };
protected:
    int             m_SocketDescriptor;
    SocketProtocol  m_SocketProtocol;
    int             m_Domain;
    SocketMode      m_Mode;

    unsigned int    m_IPAddress;
    unsigned short  m_PortNumber;
    int             m_ErrorFlag;

    std::string     m_ErrorString;

    virtual void    ProvideErrorString();

private:
    bool            SocketInit();

public:
    Socket();
    Socket(SocketMode Mode, SocketProtocol Protocol = 0, int Domain = IPv4);
    virtual ~Socket();

    virtual int             SetProtocol(SocketProtocol Protocol);
    virtual int             SetProtocol(const char* ProtocolName);
    virtual int             SetProtocol(std::string ProtocolName);

    virtual int             SetDomain(int Domain);

    virtual int             Create();
    virtual int             Bind(unsigned short PortNumber);

    virtual bool            Close();

    virtual SocketMode      GetMode();
    virtual SocketProtocol  GetProtocol();

    virtual int             GetError() const;
    virtual std::string&     GetErrorString();

    static SocketProtocol GetSocketProtocol(const char* ProtocolName);
};

#endif//__SOCKET__H_
