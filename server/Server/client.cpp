#include "client.h"

Client::Client(unsigned ind): 
	stream_packet(&Client::check_packet, this),
	status(sf::Socket::Status::Disconnected),
	index(ind)
{ };

void Client::check_packet() {
	Game& game = Game::Instance();
	Network& network = Network::Instance();

	while (status == sf::Socket::Status::Done) {
		status = socket.receive(in_packet); 
		if (status == sf::Socket::Status::Disconnected) {
			mutex.lock();

			std::cout << "Client left the server (IP: " << socket.getRemoteAddress() << ")" << std::endl;

			game.destroy_tank(index);
			for (unsigned i = (index + 1); i < network.clients.size(); i++) {
				network.clients[i]->index--;
			}
			network.clients.erase(Network::Instance().clients.begin() + index);	
			std::cout << "Count of clients: " << network.clients.size() << std::endl;

			mutex.unlock();	
		}
			
		if (status == sf::Socket::Status::Done && game.GameOn == true) {
			int key_tank, key_bullet;	
			GetDataPacket(key_tank, key_bullet);
			game.ImportToGame(key_tank, key_bullet, index);
		}
	}
}

void Client::wait_connect(sf::TcpListener &listener) {
	status = listener.accept(socket); 
	if (status == sf::Socket::Status::Done){
		std::cout << "Client join to server (IP: " << socket.getRemoteAddress() << ")" << std::endl;
		stream_packet.launch();

		mutex.lock();
		std::cout << "Count of clients: " << Network::Instance().clients.size() << std::endl;
		mutex.unlock();
	}
}
		
void Client::SendDataPacket(Map DataMap, std::vector<sf::Vector2<float>> 
	&PacketPointsTanks, std::vector<sf::Vector2<float>> &PacketPointsBullets, unsigned id) {
	out_packet.clear();
	out_packet << id;

	/*out_packet << DataMap.WIDTH << DataMap.HEIGHT;
	for (unsigned i = 0; i < DataMap.WIDTH; i++) {
		out_packet << DataMap.map[i];
	}*/

	out_packet << static_cast<unsigned int> (PacketPointsTanks.size());
	for (unsigned i = 0; i < PacketPointsTanks.size(); i++) {
		out_packet << PacketPointsTanks[i].x << PacketPointsTanks[i].y;
	}

	/*out_packet << static_cast<unsigned int> (PacketPointsBullets.size());
	for (unsigned i = 0; i < PacketPointsBullets.size(); i++) {
		out_packet << PacketPointsBullets[i].x << PacketPointsBullets[i].y;
	}*/

	socket.send(out_packet);
}

void Client::GetDataPacket(int &key_tanks, int &key_bullet) {
	in_packet.clear();
	in_packet >> key_tanks >> key_bullet;
}