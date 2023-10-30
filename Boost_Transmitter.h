#pragma once
#include "Interface.h"
#include <boost/asio.hpp>
#include <iostream>

class Boost_Transmitter :  public Transmitter {
private:

	void handle_connection(boost::asio::ip::tcp::socket&);

public:

	Boost_Transmitter();

	void run() override;

};

