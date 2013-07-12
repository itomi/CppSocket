#include "TCPSocket.h"


TCPSocket::TCPSocket() : Socket(Socket::TCP,Socket::GetSocketProtocol("TCP")), m_Connected(false) {}

TCPSocket::TCPSocket(unsigned short PortNumber)
