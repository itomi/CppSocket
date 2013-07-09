#ifndef __UDPSOCKET_H__
#define __UDPSOCKET_H__

#include "Socket.h"

class UDPSocket : public Socket
{
    int         m_Domain;
    const int   m_Type;
    const int   m_Protocol;
public:
    UDPSocket();
    virtual ~UDPSocket();

    virtual bool    Listen(int PortNumber);
    virtual int     Read(void* Buffer, int BufferSize);
    virtual int    Send(void* Buffer, int BufferSize, unsigned short PortNumber, const char* Hostname);
    virtual bool    Close();
};


#endif//__UDPSOCKET_H__
