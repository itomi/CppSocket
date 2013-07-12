#ifndef __SOCKET_EXCEPTION_H__
#define __SOCKET_EXCEPTION_H__

#include <stdexcept>
#include <string>

class SocketException : public std::runtime_error
{
public:
    explicit SocketException(std::string& ErrorMessage);
    explicit SocketException(const char* ErrorMessage);
};


#endif//__SOCKET_EXCEPTION_H__
