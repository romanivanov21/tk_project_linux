#include "tk_network_client.h"

#include <iostream>

int main(void) {
	network_client c(666);
	uint8_t init = c.network_client_init();
	uint8_t connect = c.network_client_connect();
	return 0;
}