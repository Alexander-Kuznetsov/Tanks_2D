// Server_test.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>

#include <SFML\Network.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>


typedef struct{
	float X;
	float Y;
} Point;

class Tank{
public:
	int HP;
	Point point;

	Tank::Tank(int health, float x, float y): HP(health) {
		point.X = x;
		point.Y = y;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket client_socket, server_socket;
	
	sf::TcpListener listener;
	int key;
	const float move = 1;
	const float X_player_start = 200;
	const float Y_player_start = 200;
	const int hp = 100;
	Tank player = Tank(hp, X_player_start, Y_player_start);

	sf::Packet in_packet;
	sf::Packet out_packet;
	listener.listen(2001);
	listener.accept(client_socket);

	std::string client_ip;

	while (true){
		client_socket.receive(in_packet);

		if (in_packet >> key){
			switch (key)
			{
				case sf::Keyboard::Up:
					std::cout << "Up" << std::endl;
					player.point.Y -= move;
					break;
				case sf::Keyboard::Down:
					std::cout << "Down" << std::endl;
					player.point.Y += move;
					break;
				case sf::Keyboard::Left:
					std::cout << "Left" << std::endl;
					player.point.X -= move;
					break;
				case sf::Keyboard::Right:
					std::cout << "Right" << std::endl;
					player.point.X += move;
					break;
				default:		 
					client_ip = client_socket.getRemoteAddress().toString();
					server_socket.connect(client_ip, 2000);
					break;
			}
			
			out_packet << player.point.X << player.point.Y << player.HP;
			server_socket.send(out_packet);

			out_packet.clear();
			in_packet.clear();
		}
	}


	return 0;
}

