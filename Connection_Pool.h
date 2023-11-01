#pragma once
#include "Interface.h"
#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <queue>
#include <ranges>
#include <atomic>

class Connection_Pool : 
	public Connection_Manager<boost::asio::ip::tcp::socket>{
private:

	std::vector<std::thread> threads;
	//std::queue<boost::asio::ip::tcp::socket&&> sockets;
	std::atomic_bool run;

public:

	void add_new_connection(boost::asio::ip::tcp::socket&&) override ;
	void handler();

	Connection_Pool();
	~Connection_Pool();

};

