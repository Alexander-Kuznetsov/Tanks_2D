#pragma once

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "tank.h"
#include "errors.h"
#include "client.h"

class Client;

class Network {
	public:
		unsigned port;
		unsigned max_clients;

		sf::TcpListener listener;	

		std::vector<Client*> clients;
		std::vector<Tank> tanks;

		static Network& Instance();

		Error listen_port(unsigned port);

	private:
		Network();
		Network(const Network& root);
		Network& operator=(const Network&);
};

