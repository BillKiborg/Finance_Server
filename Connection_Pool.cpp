#include "Connection_Pool.h"

void Connection_Pool::add_new_connection(boost::asio::ip::tcp::socket&& socket){



}

Connection_Pool::Connection_Pool(){

	run = true;
	for (int i = 0; i < 2; ++i) {
		threads.push_back(std::thread{ &Connection_Pool::handler, this });
	}	

}

Connection_Pool::~Connection_Pool(){	

	run = false;
	std::ranges::for_each(threads, [](std::thread& thread) {
		if (thread.joinable()) {
			thread.join();
		}
	});

}

void Connection_Pool::handler(){	

	while (run) { //атомарный флаг
		
	}
	std::cout << "Поток завершен\n";

}
