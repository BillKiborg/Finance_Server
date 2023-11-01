#include "Boost_Transmitter.h"

Boost_Transmitter::Boost_Transmitter(){

}

void Boost_Transmitter::handle_connection(boost::asio::ip::tcp::socket& socket){

	std::cout << "New connection\n";	
	std::string message;

	while (true) try {		
		
		if (socket.available()) {

			last_ping = std::chrono::system_clock::now();

			boost::asio::read_until(socket, boost::asio::dynamic_buffer(message), '\n');
			std::cout << "Message: " << message << std::endl;			
			boost::asio::write(socket, boost::asio::buffer("Status: OK\n"));			
			message.clear();
		}

		if (time_out()) {
			std::cout << "Socket close\n";
			socket.close();
			break;
		}
		
	}
	catch (std::exception& exc) {
		std::cerr << "Exc: " << exc.what() << std::endl;
		socket.close();
		break;
	}	

}

bool Boost_Transmitter::time_out(){

	auto time 
		= std::chrono::duration_cast<std::chrono::milliseconds>
									(std::chrono::system_clock::now() - last_ping).count();

	return (time > 15000 ? true : false);
}

void Boost_Transmitter::run(){

	if (!pool_manager) throw std::invalid_argument{ "Manager not found" };

	boost::asio::io_context io_context;

	using namespace boost::asio::ip;

	tcp::acceptor acceptor{ io_context, tcp::endpoint{tcp::v4(), 1111} };

	std::cout << "The Server listens on port 1111\n";

	while (true) try {

		tcp::socket socket{ io_context };
		acceptor.accept(socket);		

		pool_manager->add_new_connection(std::move(socket));

		/*std::thread th{ [this, &socket] {
			last_ping = std::chrono::system_clock::now();
			handle_connection(socket);
		} };
		th.join();*/

	}
	catch (std::exception& exc) {
		std::cerr << "Exc: " << exc.what() << std::endl;
	}	

}

void Boost_Transmitter::set_connection_manager(Connection_Manager<boost::asio::ip::tcp::socket>* _manager){
		
	std::unique_ptr<Connection_Manager <boost::asio::ip::tcp::socket>> unq{_manager};
	pool_manager = std::move(unq);

}
