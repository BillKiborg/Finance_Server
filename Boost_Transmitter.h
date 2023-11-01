#pragma once
#include "Interface.h"

#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <chrono>

class Boost_Transmitter :  public Transmitter {
private:

	std::chrono::system_clock::time_point last_ping;

	void handle_connection(boost::asio::ip::tcp::socket&);
	bool time_out();

	std::unique_ptr<Connection_Manager<boost::asio::ip::tcp::socket>> pool_manager;
	
public:

	Boost_Transmitter();

	void run() override;
	void set_connection_manager (Connection_Manager<boost::asio::ip::tcp::socket>* manager);

};

