#include "tk_network_client.h"

network_client::network_client(uint32_t port) : port_(port), s_(0) { }
network_client::~network_client() {
	//close(s_);
}
uint8_t network_client::network_client_init() {
	s_ = socket(AF_INET, SOCK_STREAM, 0);
	return (s_ < 0) ? SOCKET_OPEN_ERROR : SOCKET_OPEN_OK;
}
uint8_t network_client::network_client_connect() {
	addr_.sin_family = AF_INET;
	addr_.sin_port = htons(port_);
	addr_.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if(connect(s_,(struct sockaddr* ) &addr_, sizeof(addr_)) < 0) {
		return CLIENT_CONNECT_ERROR;
	}
	return SOCKET_OPEN_OK;
}