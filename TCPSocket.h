#ifndef __TCPSOCKET_H__
#define __TCPSOCKET_H__

class TCPSocket : public Socket {
        bool m_Connected;
        unsigned short m_PortNumber
    public:
        TCPSocket();
        TCPSocket(unsigned short PortNumber);
        TCPSocket(const char* IPAddress, unsigned short PortNumber);
        TCPSocket(std::string& IPAddress, unsigned short PortNumber);

        virtual ~TCPSocket();

        virtual int Connect(const char* IPAddress, unsigned short PortNumber);
        virtual int Disconnect();

        virtual int Send(void* Buffer, int Size);
        virtual int Receive(void* Buffer,int Size);

        virtual int Close();

};

#endif//__TCPSOCKET_H__
