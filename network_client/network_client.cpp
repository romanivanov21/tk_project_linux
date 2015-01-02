/*******************************************************
* Файл: network_client.cpp							   *
* Автор: Иванов Роман Витальевич (с)				   *
* Год: 2015											   *
* Содержит реализация класса client_network			   *
* для работы с сетью	   							   *
*													   *
*******************************************************/

#include "../shared/types_client.h"
#include "network_client.h"

#include <iostream>
#include <boost/asio.hpp>  


client_network::client_network(const std::string server_ip, const boost::uint32_t port): 
server_ip_(server_ip),
port_(port),
endpoint_(boost::asio::ip::address::from_string("192.168.1.1"),8001),
socket_(io_service_)
{
  
}
void client_network::connect_to_server()
{
	try
	{
		socket_.connect(endpoint_);
	}
	catch(...)
	{
		throw std::string("Error connect to server");
	}
}
void client_network::send_bytes(byte *data, const std::size_t &size)
{
	try
	{
		socket_.write_some(boost::asio::buffer(data,size));
	}
	catch(...)
	{
		throw std::string("Error send bytes");
	}
}
boost::int32_t client_network::read_bytes(byte *data, const std::size_t &size)
{
	boost::int32_t bytes_recived = -1;
	try
	{
		bytes_recived = socket_.read_some(boost::asio::buffer(data,size));
	}
	catch(...)
	{
		throw std::string("Error read_bytes");
	}
	return bytes_recived;
}
client_network::~client_network()
{
	socket_.close();
}