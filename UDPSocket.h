#ifndef __UDPSOCKET_H__
#define __UDPSOCKET_H__

#include "Socket.h"

class UDPSocket : public Socket
{
protected:
    int                 m_Domain;
    const int           m_Type;
    const int           m_Protocol;
    struct sockaddr_in  m_ReadSocketAddress;
    struct sockaddr_in  m_SendSocketAddress;
#ifdef __unix__
    socklen_t           m_StructureSize;
#elif _WIN32
    int                 m_Structuresize;
#endif

    bool                m_SendAddressIsSet;

public:
    UDPSocket();
    virtual ~UDPSocket();

    virtual bool    Listen(int PortNumber);
    virtual void    SetAddress(const char* IPAddress, unsigned short PortNumber);
    virtual int     Read(void* Buffer, int BufferSize);
    virtual int    Send(void* Buffer, int BufferSize);
    virtual bool    Close();
};


#endif//__UDPSOCKET_H__
