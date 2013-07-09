#ifndef _SOCKET_EXCEPTION_H_
#define _SOCKET_EXCEPTION_H_

#include <stdexcept>
#include <string>

class SocketException : public std::runtime_error
{
public:
    explicit SocketException(std::string& ErrorMessage);
    explicit SocketException(const char* ErrorMessage);
};


#endif//_SOCKET_EXCEPTION_H_
