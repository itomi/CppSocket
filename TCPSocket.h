#ifndef __TCPSOCKET_H__
#define __TCPSOCKET_H__

#include "Socket.h"

class TCPSocket : public Socket
{
public:
    enum TCPSocketMode
    {
        Server,
        Client,
        NotSet
    };

private:
    bool				m_Connected;
    unsigned short		m_PortNumber;
    TCPSocketMode       m_TCPMode;
protected:
	virtual u_long		NumberOfBytesInBuffer();

public:
    TCPSocket();
    TCPSocket(TCPSocket& TCPSocketObject);
    TCPSocket(Socket& SocketObject);
    TCPSocket(unsigned short PortNumber);
    TCPSocket(const char* IPAddress, unsigned short PortNumber);
    TCPSocket(std::string& IPAddress, unsigned short PortNumber);

    virtual ~TCPSocket();

    virtual int         Connect(const char* IPAddress, unsigned short PortNumber);
    virtual int         Connect(std::string& IPAddress, unsigned short PortNumber);
    virtual int         Disconnect();

    virtual TCPSocket*  Accept();

    virtual int         Send(const void* Buffer, int Size);
    virtual int         Receive(const void* Buffer,int Size);

    virtual bool        Close();

	friend Socket& operator<<(TCPSocket& socket, ISendable& objectToSend) {
		std::stringstream buffer("");
		objectToSend.send(buffer);

		std::string preparedBuffer = buffer.str();

		socket.Write(preparedBuffer.c_str(), preparedBuffer.size());
		return socket;
	}

	friend Socket& operator>>(TCPSocket& socket, ISendable& objectToRecv) {
		u_long bytesToRead = socket.NumberOfBytesInBuffer();
		char* sockbuff = new char[bytesToRead];
		if(socket.Read(sockbuff, bytesToRead)) {
			std::stringstream buffer("");
			buffer<<sockbuff<<std::ends;
			objectToRecv.recv(buffer);
			delete sockbuff;
			return socket;
		} else {
			delete sockbuff;
			//throw SocketException(EMPTY_BUFFER_MESSAGE);
			return socket;
		}
	}


};

#endif//__TCPSOCKET_H__
