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

public:

	Boost_Transmitter();

	void run() override;

};

