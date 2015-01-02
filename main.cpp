#include <iostream>
#include <boost/asio.hpp>
#include "network_client/network_client.h"
#include "shared/types_client.h"

void sync_echo() 
{
	byte destBuff[8];
	client_network ntw("192.168.1.1", 8001);
	ntw.connect();
	ntw.read_bytes(destBuff,8);
	for(std::size_t i = 0; i < 8; i++)
	{
		std::cout<<destBuff[i];
	}
	std::cout<<std::endl;
}

int main() 
{
	try{
	sync_echo();
	}
	catch(std::string e)
	{
		std::cout<<e<<std::endl;
	}
	getchar();
	return 0;
}