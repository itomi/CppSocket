#include "UDPSocket.h"

UDPSocket::UDPSocket() : Socket(), m_Domain(AF_INET), m_Type(SOCK_DGRAM), m_Protocol(0) {
    if( (this->m_SocketDescriptor = socket(m_Domain, m_Type, m_Protocol)) != 0 ){
        this->m_ErrorString = strerror(errno);
        this->m_ErrorFlag = errno;
    }else{
        this->m_ErrorFlag = 0;
    }
}

UDPSocket::~UDPSocket() {
    if(this->IsWorking())
        this->Close();
}

bool UDPSocket::Listen(int PortNumber) {
    struct sockaddr_in TemporarySocketAddress;
    memset(&TemporarySocketAddress, 0, sizeof(TemporarySocketAddress));
    if(this->m_ErrorFlag == 0) {
        TemporarySocketAddress.sin_family = AF_INET;
        TemporarySocketAddress.sin_port = PortNumber;
        TemporarySocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);

        if(bind(this->m_SocketDescriptor, (struct sockaddr*) &TemporarySocketAddress, sizeof(struct sockaddr_in)) == -1 ) {
            this->m_ErrorString = strerror(errno);
            this->m_ErrorFlag = errno;
            return false;
        }
    }
    return false;
}

bool UDPSocket::Send(char* Buffer, int BufferSize) {
    return true;
}

bool UDPSocket::Close() {
    return true;
}
