#include "game.h"

Game::Game() { };
Game::Game(const Game& root) { }
Game& Game::operator=(const Game&) { return *this; }

Game& Game::Instance() {
	static Game singleton;
	return singleton;
}

void Game::wait_clients() {
	std::cout << "Wait clients!" << std::endl;
	Network& network = Network::Instance();
	GameOn = false;

	while (network.clients.size() < network.max_clients) {
		gameMutex.lock();

		Client* client = new Client(network.clients.size());
		network.clients.push_back(client);
		client->wait_connect(network.listener);
				
		gameMutex.unlock();
	}
}

void Game::start_game() {
	Map DataMap;
	Network &network = Network::Instance();
	DataMap.LoadMap(network.max_clients);
	speed_tank = 1;
	speed_bullet = 2;

	std::cout << "Game starts!" << std::endl;
			
	create_tanks(DataMap.PlayerPoints);
	GameOn = true;

			
	while (GameOn){
		std::vector<sf::Vector2<float>> PacketPointsTanks;
		std::vector<sf::Vector2<float>> PacketPointsBullets;
		std::vector<RouteObject> route_tanks;

		gameMutex.lock();
		for (unsigned i = 0; i < network.tanks.size(); i++) {
			MoveBullets(network.tanks[i].bullets, speed_bullet);
		}
		gameMutex.unlock();

		gameMutex.lock();
		for (unsigned i = 0; i < network.tanks.size(); i++) {
			PacketPointsTanks.push_back(network.tanks[i].point);
			route_tanks.push_back(network.tanks[i].turn);
			
			for (unsigned j = 0; j < network.tanks[i].bullets.size(); j++) {
				PacketPointsTanks.push_back(network.tanks[i].bullets[j].point);
			}
		}
		gameMutex.unlock();

		//std::cout << "PACKET  " << PacketPointsTanks[0].x << PacketPointsTanks[0].y;

		gameMutex.lock();
		for (unsigned i = 0; i < network.clients.size(); i++) {
			network.clients[i]->SendDataPacket(DataMap, PacketPointsTanks, PacketPointsBullets, route_tanks,  i);
		}
		gameMutex.unlock();

		
	}
}

void Game::create_tanks(std::vector<sf::Vector2<float>> points) {
	for (unsigned i = 0; i < Network::Instance().clients.size(); i++) {
		Tank tank = Tank(100, points[i].x, points[i].y, RouteObject::Up, i);
		Network::Instance().tanks.push_back(tank);
	}
}

void Game::destroy_tank(unsigned id) {
	Network &network = Network::Instance();
	gameMutex.lock();
	network.tanks.erase(Network::Instance().tanks.begin() + id);	
	gameMutex.unlock();
}

void Game::end_game() {
	return;
}

/*void Game::ImportToGame(int key_tank, int key_bullet, unsigned id) {		
	gameMutex.lock();

	Network &network = Network::Instance();
	MoveTank(network.tanks[id], key_tank, speed_tank);
	std::cout << network.tanks[id].point.x << "   " << network.tanks[id].point.x << std::endl;
	if (key_bullet == RouteObject::Space) {
		Bullet bullet = Bullet(network.tanks[id].point.x, 
			network.tanks[id].point.y, network.tanks[id].turn, network.tanks[id].team); 
		network.tanks[id].bullets.push_back(bullet);
	}

	MoveBullets(network.tanks[id].bullets, speed_bullet);

	gameMutex.unlock();
}*/

void Game::ImportToGame(int key, unsigned id) {		
	Network &network = Network::Instance();
	
	if (key == RouteObject::Space) {
		gameMutex.lock();
		Bullet bullet = Bullet(network.tanks[id].point.x, 
			network.tanks[id].point.y, network.tanks[id].turn, network.tanks[id].team); 
		network.tanks[id].bullets.push_back(bullet);
		gameMutex.unlock();
	}
	else{
		gameMutex.lock();
		MoveTank(network.tanks[id], key, speed_tank);
		std::cout << network.tanks[id].point.x << "   " << network.tanks[id].point.y << std::endl;
		gameMutex.unlock();
	}
}