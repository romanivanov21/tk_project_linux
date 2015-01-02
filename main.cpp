#include <iostream>
#include "network_client/network_client.h"
#include "shared/types_client.h"

void sync_echo() 
{
	client_network net("192.168.1.1", 8001);
	net.connect_to_server();
	char buf[1024];
	strcpy(buf,"I is client");
	net.send_bytes((byte*)buf,1024);
	char destBuff[8];
	memset(destBuff,0,8);

	net.read_bytes((byte*)destBuff,8);
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