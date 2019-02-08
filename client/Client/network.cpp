#include "network.h"

Error Network::connect_to_server(){
	std::cout << "Connect to server, IP address: ";
	std::cin >> server_ip;

	if (socket.connect(server_ip, 2001, sf::seconds(15)) != sf::Socket::Done) {	
		std::cerr << std::endl << "Failed connect to the server" << std::endl;
		return ConnectError;
	}
	else {
		std::cout << std::endl << "You are connected to the server" << std::endl;
		return Ok;
	}
}

void Network::ReceivePacket() {
	socket.receive(in_packet);
}

void Network::PushInPacket(int data) {
	out_packet << data;
}
		
void Network::SendPacket() {
	socket.send(out_packet);
}

void Network::ClearOutPacket() {
	out_packet.clear();
}

void Network::ClearInPacket() {
	in_packet.clear();
}

void Network::ReadDataFromPacket(sf::RenderWindow &window) {
	int id;
	float x, y;
	unsigned count_tanks, count_bullets;

	in_packet >> id;

	Map download_map;
	std::string tmp;
	in_packet >> download_map.WIDTH >> download_map.HEIGHT;
	for (unsigned i = 0; i < download_map.WIDTH; i++){
		in_packet >> tmp;
		download_map.map.push_back(tmp);
	}
	download_map.DrawMap(window);

	unsigned turn;
	in_packet >> count_tanks;
	for (unsigned i = 0; i < count_tanks; i++){
		in_packet >> x;
		in_packet >> y;
		in_packet >> turn;
		Tank player = Tank(100, x, y, (TurnObject)turn);
		player.DrawTank(window);
	}

	in_packet >> count_bullets;
	for (unsigned i = 0; i < count_bullets; i++){
		in_packet >> x;
		in_packet >> y;
		Bullet bullet = Bullet(x, y);
		bullet.DrawBullet(window);
	}		
}