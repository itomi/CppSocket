#include "UDPSocket.h"

UDPSocket::UDPSocket() : Socket(), m_Domain(AF_INET), m_Type(SOCK_DGRAM), m_Protocol(0)
{
    if( (this->m_SocketDescriptor = socket(m_Domain, m_Type, m_Protocol)) == -1 )
    {
#ifdef __unix__
        this->m_ErrorFlag = errno;
#elif _WIN32
        this->m_ErrorFlag = WSAGetLastError();
#endif
        this->m_ErrorString = std::string(strerror(this->m_ErrorFlag));
        throw SocketException();
    }
    else
    {
        this->m_ErrorFlag = 0;
    }
}

UDPSocket::~UDPSocket()
{
    this->Close();
}

bool UDPSocket::Listen(int PortNumber)
{
    struct sockaddr_in TemporarySocketAddress;
    memset(&TemporarySocketAddress, 0, sizeof(TemporarySocketAddress));
    if(this->m_ErrorFlag == 0)
    {
        TemporarySocketAddress.sin_family = AF_INET;
        TemporarySocketAddress.sin_port = htons(PortNumber);
        TemporarySocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);

        if(bind(this->m_SocketDescriptor, (struct sockaddr*) &TemporarySocketAddress, sizeof(struct sockaddr_in)) == -1 )
        {
            this->m_ErrorString = strerror(errno);
            this->m_ErrorFlag = errno;
            return false;
        }
    }
    return false;
}

int UDPSocket::Read(void* Buffer, int BufferSize)
{
    if( this->m_SocketDescriptor == -1 )
        return -1;
    return recv( this->m_SocketDescriptor, (char*)Buffer, BufferSize, 0);
}

bool UDPSocket::Send(void* Buffer, int BufferSize, unsigned short PortNumber, const char* Hostname)
{
    if( this->m_SocketDescriptor == -1 )
        return false;

    struct sockaddr_in SocketAddress;

    memset(&SocketAddress, 0, sizeof(struct sockaddr_in));

    SocketAddress.sin_family = AF_INET;
    SocketAddress.sin_addr.s_addr = inet_addr(Hostname);
    SocketAddress.sin_port = htons(PortNumber);

    memset(SocketAddress.sin_zero, 0, sizeof(SocketAddress.sin_zero));

#ifdef WIN32_OLD
    return sendto(this->m_SocketDescriptor, (char*)Buffer, BufferSize, 0, (struct sockaddr*)&SocketAddress, sizeof(struct sockaddr));
#else
    return sendto(this->m_SocketDescriptor, Buffer, BufferSize, 0, (struct sockaddr*)&SocketAddress, sizeof(struct sockaddr));
#endif
}

bool UDPSocket::Close()
{
    return true;
}
