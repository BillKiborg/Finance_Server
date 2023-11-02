#include "Boost_Transmitter.h"

Boost_Transmitter::Boost_Transmitter(){

}

void Boost_Transmitter::run(){

	if (!pool_manager) throw std::invalid_argument{ "Manager not found" };

	using namespace boost::asio::ip;
	boost::asio::io_context io_context;
	tcp::acceptor acceptor{ io_context, tcp::endpoint{tcp::v4(), 1111} };

	std::cout << "The Server listens on port 1111\n";

	while (true) try {

		tcp::socket socket{ io_context };
		acceptor.accept(socket);
		pool_manager->add_new_connection(std::move(socket));		

	}
	catch (std::exception& exc) {
		std::cerr << "Exc: " << exc.what() << std::endl;
	}	

}

void Boost_Transmitter::set_connection_manager(Connection_Manager<boost::asio::ip::tcp::socket>* _manager){
		
	std::unique_ptr<Connection_Manager <boost::asio::ip::tcp::socket>> unq{_manager};
	pool_manager = std::move(unq);

}
