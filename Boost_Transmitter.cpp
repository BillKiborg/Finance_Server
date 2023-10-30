#include "Boost_Transmitter.h"

Boost_Transmitter::Boost_Transmitter(){

}

void Boost_Transmitter::handle_connection(boost::asio::ip::tcp::socket& socket){

	std::cout << "New connection\n";

	boost::system::error_code error_code;
	std::string message;

	do {
		boost::asio::read_until(socket, boost::asio::dynamic_buffer(message), "\n");
		std::cout << "Message: " << message << std::endl;
		boost::asio::write(socket, boost::asio::buffer("Status: OK\n"), error_code);
		if (message == "\n") return;
	}
	while (!error_code);

}

void Boost_Transmitter::run(){

	boost::asio::io_context io_context;

	using namespace boost::asio::ip;

	tcp::acceptor acceptor{ io_context, tcp::endpoint{tcp::v4(), 1111} };

	std::cout << "The Server listens on port 1111\n";

	while (true) try {

		tcp::socket socket{ io_context };
		acceptor.accept(socket);
		handle_connection(socket);

	}
	catch (std::exception& exc) {
		std::cerr << "Exc: " << exc.what() << std::endl;
	}

}
