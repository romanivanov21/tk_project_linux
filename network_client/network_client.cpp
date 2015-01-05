/*******************************************************
* Файл: network_client.cpp							   *
* Автор: Иванов Роман Витальевич (с)				   *
* Год: 2015											   *
* Содержит реализация класса client_network			   *
* для работы с сетью	   							   *
*													   *
*******************************************************/

#include "../shared/gost_types_convert.h"
#include "../crypt_gost_28147-89/crypt_gost_types.h"
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
void client_network::gost_decrypt_data(byte *data, std::size_t &size, const word32 *key)
{
	word32 word32_data[2];
	byte byte_data[8];
	memset(word32_data,0,8);
	memset(byte_data,0,8);
	word32 crypt_word32_data[2];
	byte crypt_byte_data[8];
	memset(crypt_word32_data, 0, 8);
	memset(crypt_byte_data, 0, 8);
	std::size_t number_blocks = 0; //количество блоков для шифрования
	if(size % 8 != 0)
	{
		number_blocks = (size / 8) + 1;
	}
	else
	{
		number_blocks = (size / 8);
	}
	
	std::size_t i = 0;
	std::size_t i_blocks = 1;
	while(i_blocks <= number_blocks)
	{
		std::size_t i_data = 0;
		for(std::size_t n_byte = i; (n_byte < (i + 8)); n_byte++)
		{
			byte_data[i_data] = data[n_byte];
			i_data++;
		}
		key_box_init();
		byte_to_word32_data(byte_data, word32_data);
		gostdecrypt(word32_data,crypt_word32_data, key);
		word32_to_byte_data(crypt_word32_data, crypt_byte_data);
		i_data = 0;
		for(std::size_t n_byte = i; (n_byte < (i + 8)); n_byte++)
		{
			data[n_byte] = crypt_byte_data[i_data];
			i_data++;
		}
		i+=8;
		i_blocks++;
	}
}
void client_network::gost_crypt_data(byte *data, std::size_t &size, const word32 *key)
{
	word32 word32_data[2];
	byte byte_data[8];
	memset(word32_data,0,8);
	memset(byte_data,0,8);
	word32 crypt_word32_data[2];
	byte crypt_byte_data[8];
	memset(crypt_word32_data, 0, 8);
	memset(crypt_byte_data, 0, 8);
	std::size_t number_blocks = 0; //количество блоков для шифрования
	if(size % 8 != 0)
	{
		number_blocks = (size / 8) + 1;
	}
	else
	{
		number_blocks = (size / 8);
	}
	
	std::size_t i = 0;
	std::size_t i_blocks = 1;
	while(i_blocks <= number_blocks)
	{
		std::size_t i_data = 0;
		for(std::size_t n_byte = i; (n_byte < (i + 8)); n_byte++)
		{
			byte_data[i_data] = data[n_byte];
			i_data++;
		}
		key_box_init();
		byte_to_word32_data(byte_data, word32_data);
		gostcrypt(word32_data,crypt_word32_data, key);
		word32_to_byte_data(crypt_word32_data, crypt_byte_data);

		i_data = 0;
		for(std::size_t n_byte = i; (n_byte < (i + 8)); n_byte++)
		{
			data[n_byte] = crypt_byte_data[i_data];
			i_data++;
		}
		i+=8;
		i_blocks++;
	}
}
client_network::~client_network()
{
	socket_.close();
}