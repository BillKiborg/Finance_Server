#include "Connection_Pool.h"

Connection_Pool::~Connection_Pool(){

	run_flag = false;
	for (auto& thread : threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}

}

Connection_Pool::Connection_Pool(){
	setup();
}

void Connection_Pool::setup() {

	run_flag = true;
	for (int i = 0; i < 1; ++i)	{
		threads.push_back(std::thread{ &Connection_Pool::work, this });
	}
}

void Connection_Pool::work(){
		
	while (run_flag) try {		

		std::unique_ptr<Connection>	connection{ get_connection() };

		auto message = connection->read(8000);
		std::cout << "Msg: " << message << "\n";

		std::this_thread::sleep_for(std::chrono::seconds{ 10 });

		std::stringstream stream;
		
		std::string html{
					"<!DOCTYPE html>"
					"<html>"
					"<head>"
						"<title>Пример страницы</title>"
					"</head>"
					"<body>"
						"<h1>Привет, это Сервер!</h1>"
					"</body>"
					"</html>"
		};

		std::string responce{
			"HTTP/1.1 200 OK\r\n"
			"Content-Type: text/html\r\n"
			"Content-Length: " + std::to_string(html.size()) + "\r\n\r\n" + html
		};

		connection->write(responce);

		connection->close();
		std::this_thread::sleep_for(std::chrono::nanoseconds{ 1 });

	}
	catch (std::exception& exc) {
		std::cout << "Exc: " << exc.what() << "\n";
	}

}

Connection* Connection_Pool::get_connection(){

	while (run_flag) {

		std::unique_lock<std::mutex> lock{ mutex };

		if (!connections.empty()) {

			auto connection = connections.front();
			connections.pop();
			return connection;
		}		
		std::this_thread::sleep_for(std::chrono::nanoseconds{ 1 });
	}

	throw std::runtime_error{ "Connection_Pool - Run flag = false" };
	
}

void Connection_Pool::add_connection(Connection* new_connection){

	std::cout << "Новое соединение\n";
	std::unique_lock<std::mutex> lock{ mutex };
	connections.push(new_connection);

}

void Connection_Pool::del_connection(Connection*){
}
