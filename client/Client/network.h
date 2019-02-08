#pragma once

#include <SFML\Network.hpp>
#include <iostream>
#include "tank.h"
#include "map.h"

#include "errors.h"

class Network {
	public:
		sf::TcpSocket socket;
		sf::Packet out_packet, in_packet;
		sf::IpAddress server_ip;

		Error connect_to_server();

		void ReceivePacket();
		void PushInPacket(int data);
		void SendPacket();

		void ClearOutPacket();
		void ClearInPacket();

		void ReadDataFromPacket(sf::RenderWindow &window);
};