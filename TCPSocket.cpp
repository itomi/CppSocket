#include "TCPSocket.h"


TCPSocket::TCPSocket()
    : Socket(Socket::TCP,Socket::GetSocketProtocol("TCP")),
    m_Connected(false),
    m_TCPMode(TCPSocket::NotSet) {}

TCPSocket::TCPSocket(unsigned short PortNumber)
    : Socket(Socket::TCP, Socket::GetSocketProtocol("TCP")),
    m_Connected(false),
    m_TCPMode(TCPSocket::Server)
{
    this->Create();
    this->Listen(PortNumber);
}

TCPSocket::TCPSocket(const char* IPAddress, unsigned short PortNumber)
    : Socket(Socket::TCP, Socket::GetSocketProtocol("TCP")),
    m_Connected(true),
    m_TCPMode(TCPSocket::Client)
{
    this->Create();
    Socket::Connect(IPAddress, PortNumber);
}

TCPSocket::TCPSocket(std::string& IPAddress, unsigned short PortNumber)
    : Socket(Socket::TCP, Socket::GetSocketProtocol("TCP")),
    m_Connected(true),
    m_TCPMode(TCPSocket::Client)
{
    this->Create();
    try{
        Socket::Connect(IPAddress, PortNumber);
        }catch(SocketException& e) {
            m_Connected = false;
            throw SocketException(e.what());
        }
}

TCPSocket::~TCPSocket()
{
    if(m_Connected)
        this->Disconnect();
}

int TCPSocket::Disconnect()
{
    if(!m_Connected)
    {
        throw SocketException("TCPSocket is not connected!");
        return -1;
    }
    return Socket::Close();
}

int TCPSocket::Send(void* Buffer, int Size)
{
    if(m_Connected || m_TCPMode == Server)
        return Socket::Write(Buffer, Size);

    throw SocketException("TCPSocket not connected.");
    return -1;
}

int TCPSocket::Receive(void* Buffer, int Size)
{
    return Socket::Read(Buffer, Size);
}

bool TCPSocket::Close()
{
    return Socket::Close();
}
