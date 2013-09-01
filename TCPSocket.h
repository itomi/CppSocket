#ifndef __TCPSOCKET_H__
#define __TCPSOCKET_H__

#include "Socket.h"

class TCPSocket : public Socket
{
public:
    enum TCPSocketMode
    {
        Server,
        Client,
        NotSet
    };

private:
    bool               m_Connected;
    unsigned short    m_PortNumber;
    TCPSocketMode       m_TCPMode;

public:
    TCPSocket();
    TCPSocket(TCPSocket& TCPSocketObject);
    TCPSocket(Socket& SocketObject);
    TCPSocket(unsigned short PortNumber);
    TCPSocket(const char* IPAddress, unsigned short PortNumber);
    TCPSocket(std::string& IPAddress, unsigned short PortNumber);

    virtual ~TCPSocket();

    virtual int         Connect(const char* IPAddress, unsigned short PortNumber);
    virtual int         Connect(std::string& IPAddress, unsigned short PortNumber);
    virtual int         Disconnect();

    virtual TCPSocket*  Accept();

    virtual int         Send(const void* Buffer, int Size);
    virtual int         Receive(const void* Buffer,int Size);

    virtual bool        Close();
};

#endif//__TCPSOCKET_H__
