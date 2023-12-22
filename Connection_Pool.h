#pragma once
#include "Connection_Manager.h"
#include "Connection.h"

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <atomic>
#include <sstream>

class Connection_Pool : public Connection_Manager {
private:

	std::vector<std::thread> threads;
	std::queue<Connection*> connections;

	std::mutex mutex;
	std::atomic_bool run_flag = false;

	void setup();
	void work();

	Connection* get_connection();

public:

	~Connection_Pool();
	Connection_Pool();

	void add_connection(Connection*) override;
	void del_connection(Connection*) override;

};