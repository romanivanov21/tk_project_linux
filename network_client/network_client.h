/*******************************************************
* Файл: network_client.h							   *
* Автор: Иванов Роман Витальевич (с)				   *
* Год: 2015											   *
* Содержит объявление класса client_network 		   *
* для работы с сетью	   							   *
*													   *
*******************************************************/
#ifndef _NETWORK_CLIENT_H_
#define _NETWORK_CLIENT_H_

#include <boost/asio.hpp>

#include "../crypt_gost_28147-89/crypt_gost_types.h"
#include "../shared/gost_include.h"

class client_network
{
public:
	explicit client_network(const std::string server_ip, const boost::uint32_t port);

	void connect_to_server();
	void send_bytes(byte *data, const std::size_t &size);
	boost::int32_t read_bytes(byte *data, const std::size_t &size);

	boost::uint32_t current_port()const { return port_; }
	std::string current_server_ip_address()const { return server_ip_; }

	~client_network();
private:
	void gost_decrypt_data(byte *data, std::size_t &size, const word32 *key);
	void gost_crypt_data(byte *data, std::size_t &size, const word32 *key);
private:
	std::string server_ip_;
	boost::uint32_t port_;
	
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::endpoint endpoint_;
	boost::asio::ip::tcp::socket socket_;
};

#endif