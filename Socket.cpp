#include "Socket.h"


Socket::Socket() : m_SocketDescriptor(0), m_IPAddress(0), m_PortNumber(0), m_ErrorFlag(0), m_Mode(UNINITIALIZED)
{
    if( this->SocketInit() == false )
        this->m_ErrorFlag = -1;

}

Socket::~Socket() {}

bool Socket::SocketInit()
{
#ifdef _WIN32
    WSADATA wsdat;
    memset(&wsdat, 0, sizeof(wsdat));

    if(WSAStartup(MAKEWORD(2,2), &wsdat))
        return false;
#endif
    return true;
}

int Socket::GetError() const
{
    return (this->m_ErrorFlag);
}

SocketProtocol Socket::GetSocketProtocol(const char* Protocol)
{
    struct protoent *TempProtoStruct;
    int ProtocolNumber;

    TempProtoStruct = getprotobyname(Protocol);
    ProtocolNumber = TempProtoStruct->p_proto;
    endprotoent();

    return ProtocolNumber;
}
