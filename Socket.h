#ifndef __SOCKET__H_
#define __SOCKET__H_

#include <iostream>
#include <string>

#ifdef __unix__
#   include <sys/types.h>
#   include <sys/socket.h>
#   include <sys/un.h>
#   include <netinet/in.h>
#else
#   include <windows.h>
#   include <winsock.h>
#endif

typedef int SocketProtocol;

class Socket {
    protected:
        int             m_SocketDescriptor;

        unsigned int    m_IPAddress;
        int             m_PortNumber;
        int             m_ErrorFlag;

        std::string     m_ErrorString;

    private:
        bool            SocketInit();

    public:
        Socket();
        Socket(SocketProtocol Protocol);
        virtual ~Socket();

        virtual int     GetError() const;

        virtual bool    Listen(int PortNumber) = 0;
        virtual bool    Send() = 0;
        virtual bool    Close() = 0;

        virtual bool    IsWorking();

        static SocketProtocol GetSocketProtocol(const char* ProtocolName);
};

#endif//__SOCKET__H_
