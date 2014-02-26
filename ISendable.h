#pragma once
#include <iostream>

class ISendable {
public:
	virtual int send(std::stringstream& outstream) = 0;
	virtual int recv(std::stringstream& istream) = 0;
	ISendable(void);
	virtual ~ISendable(void);
};
