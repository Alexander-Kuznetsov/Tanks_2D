#include "network.h"

Network::Network() { };
Network::Network(const Network& root) { }
Network& Network::operator=(const Network&){ return *this; }

Error Network::listen_port(unsigned port) {
	if (listener.listen(port) != sf::Socket::Done) {
		std::cout << "Failed open Port " << port << std::endl;
		// system("pause");
		return PortNotOpen;
	}
	return Ok;
}

Network& Network::Instance() {
	static Network singleInstance;
	return singleInstance;
}

