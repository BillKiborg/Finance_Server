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
	std::queue<boost::asio::ip::tcp::socket> new_sockets;
	std::mutex mutex_new_sockets;
	std::atomic_bool run;

	bool time_out(std::chrono::system_clock::time_point, size_t delay);

public:

	void add_new_connection(boost::asio::ip::tcp::socket&&) override ;
	void connection_handler();	

	Connection_Pool();
	~Connection_Pool();

};

