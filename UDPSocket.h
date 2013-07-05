#ifndef __UDPSOCKET_H__
#define __UDPSOCKET_H__

#include "Socket.h"

class UDPSocket : public Socket {
        int         m_Domain;
        const int   m_Type;
        const int   m_Protocol;
    public:
        UDPSocket();
        virtual ~UDPSocket();

        virtual bool    Listen(int PortNumber);
        virtual bool    Send(char* Buffer, int BufferSize);
        virtual bool    Close();
};


#endif//__UDPSOCKET_H__
