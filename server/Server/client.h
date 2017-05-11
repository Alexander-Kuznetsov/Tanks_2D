#pragma once

#include <SFML/Network.hpp>

#include "game.h"
#include "map.h"

class Client {
	private:
		sf::Thread stream_packet;		
		sf::Mutex mutex;
		
		void check_packet();

	public:
		sf::Packet in_packet, out_packet;
		sf::TcpSocket socket;
		sf::Socket::Status status;
		volatile unsigned index;

		Client(unsigned ind);

		void wait_connect(sf::TcpListener &listener);
		//void GetDataPacket(int &key_tanks, int &key_bullet);
		void GetDataPacket(int &key);
		void SendDataPacket(Map DataMap, std::vector<sf::Vector2<float>> 
			&PacketPointsTanks, std::vector<sf::Vector2<float>> &PacketPointsBullets, std::vector<RouteObject> &route_tanks, unsigned id);
};