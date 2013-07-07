#include "Socket.h"

void Socket::ProvideErrorString()
{
#ifdef __unix__
    m_ErrorFlag = errno;
#elif _WIN32
    m_ErrorFlag = WSAGetLastError();
#endif
    m_ErrorString = std::string(strerror(m_ErrorFlag));
}

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

Socket::Socket()
    : m_SocketDescriptor(0),
    m_Mode(UNINITIALIZED),
    m_IPAddress(0),
    m_PortNumber(0),
    m_ErrorFlag(0)
{
    if( this->SocketInit() == false )
    {
        ProvideErrorString();
        throw SocketException(m_ErrorString);
    }
}

Socket::Socket(SocketMode Mode, SocketProtocol Protocol, int Domain )
    : m_SocketDescriptor(0),
    m_SocketProtocol(Protocol),
    m_Domain(Domain),
    m_Mode(Mode),
    m_IPAddress(0),
    m_PortNumber(0),
    m_ErrorFlag(0)
{
    if( this->SocketInit() == false )
    {
        ProvideErrorString();
        throw SocketException(m_ErrorString);
    }
}

Socket::~Socket() {}

int Socket::SetProtocol(SocketProtocol Protocol)
{
    if(this->m_SocketDescriptor == 0)
    {
        this->m_SocketProtocol = Protocol;
        return Protocol;
    }
    return -1;
}

int Socket::SetProtocol(const char* ProtocolName)
{
    return (this->SetProtocol(Socket::GetSocketProtocol(ProtocolName)));
}

int Socket::SetProtocol(std::string ProtocolName)
{
    return (this->SetProtocol(ProtocolName.c_str()));
}

int Socket::SetDomain(int Domain)
{
    if( this->m_SocketDescriptor <= 0 )
    {
        this->m_Domain = Domain;
        return Domain;
    }
    return -1;
}

int Socket::Create()
{
    if( this->m_SocketDescriptor == 0)
    {
        if( (this->m_SocketDescriptor = socket(this->m_Domain, this->m_Mode, this->m_SocketProtocol)) == -1)
        {
            ProvideErrorString();
            throw SocketException(m_ErrorString);
        }

        return this->m_SocketDescriptor;
    }

    throw SocketException("Socket is already created.");
    return -1;
}

int Socket::Bind(unsigned short PortNumber)
{
    struct sockaddr_in  TemporaryBindAddress_IPv4;
    struct sockaddr_in6 TemporaryBindAddress_IPv6;
    if( this->m_SocketDescriptor > 0 )
    {
        if( this->m_Domain == IPv4 )
        {
            memset(&TemporaryBindAddress_IPv4, 0, sizeof(struct sockaddr_in));

            TemporaryBindAddress_IPv4.sin_family = IPv4;
            TemporaryBindAddress_IPv4.sin_port = htons(PortNumber);
            TemporaryBindAddress_IPv4.sin_addr.s_addr = inet_addr(INADDR_ANY);

            if( (bind(this->m_SocketDescriptor, (struct sockaddr*)&TemporaryBindAddress_IPv4, sizeof(struct sockaddr) )) == -1 )
            {
                ProvideErrorString();
                throw SocketException(m_ErrorString);
            }
            this->m_PortNumber = PortNumber;
        }
        else if ( this->m_Domain == IPv6 )
        {
            memset(&TemporaryBindAddress_IPv6, 0, sizeof(struct sockaddr_in6));

            TemporaryBindAddress_IPv6.sin6_family = IPv6;
        }
    }

    throw SocketException("Socket is not created.");
    return -1;
}

bool Socket::Close()
{
    if( this->m_SocketDescriptor > 0 )
    {
#ifdef __unix__
        if(close(this->m_SocketDescriptor) == -1)
#elif _WIN32
        if(closesocket(this->m_SocketDescriptor) == -1)
#endif
        {
            ProvideErrorString();
            throw SocketException(m_ErrorString);
            return false;
        }
        return true;
    }
    return false;
}

SocketMode Socket::GetMode()
{
    return this->m_Mode;
}

SocketProtocol Socket::GetProtocol()
{
    return this->m_SocketProtocol;
}

int Socket::GetError() const
{
    return (this->m_ErrorFlag);
}

std::string& Socket::GetErrorString()
{
    return this->m_ErrorString;
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
