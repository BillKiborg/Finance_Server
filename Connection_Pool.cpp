#include "Connection_Pool.h"

bool Connection_Pool::time_out(std::chrono::system_clock::time_point last_ping, size_t delay) {

	size_t time
		= std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now() - last_ping).count();

	return (time > delay ? true : false);
}

void Connection_Pool::add_new_connection(boost::asio::ip::tcp::socket&& socket){
	
	std::unique_lock<std::mutex> lock{ mutex_new_sockets };
	new_sockets.push(std::move(socket));	

}

Connection_Pool::Connection_Pool(){

	run = true;
	for (int i = 0; i < 2; ++i) {
		threads.push_back(std::thread{ &Connection_Pool::connection_handler, this });
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


void Connection_Pool::connection_handler(){	

	boost::asio::io_context io_context;
	boost::asio::ip::tcp::socket socket{ io_context };

	while (run)	{

		while (true) {

			std::unique_lock<std::mutex> lock{ mutex_new_sockets };
			if (!new_sockets.empty()) {
				socket = std::move(new_sockets.front());
				new_sockets.pop();
				break;
			}
			std::this_thread::yield();
		}

		std::cout << "����� ���������\n";
		std::string message;
		std::chrono::system_clock::time_point last_ping = std::chrono::system_clock::now();
		while (true) try {

			if (socket.available()) {

				last_ping = std::chrono::system_clock::now();

				boost::asio::read_until(socket, boost::asio::dynamic_buffer(message), '\n');
				std::cout << "Message: " << message << std::endl;
				boost::asio::write(socket, boost::asio::buffer("Status: OK\n"));
				message.clear();
			}

			if (time_out(last_ping, 6000)) {
				socket.close();
				std::cout << "Socket close\n";
				break;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds{ 1 });

		}
		catch (std::exception& exc) {
			std::cerr << "Exc: " << exc.what() << std::endl;
			socket.close();
			break;
		}
	}

}
