#ifndef _TK_NETWORK_CLIENT_H_
#define _TK_NETWORK_CLIENT_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

class network_client
{
public:
	network_client(uint32_t port);

	uint8_t network_client_init();
	uint8_t network_client_connect();
	~network_client();
private:
	int s_;
	struct sockaddr_in addr_;
	uint32_t port_;
};

enum RETURN_CLIENT {
	SOCKET_OPEN_OK = 0,
	SOCKET_OPEN_ERROR = 1,
	CLIENT_CONNECT_ERROR = 2
};

#endif