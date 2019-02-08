#pragma once

#include "map.h"
#include "logic.h"
#include "network.h"
#include "client.h"

class Game {
	private:
		sf::Mutex gameMutex;
		Game();
		Game(const Game& root);
		Game& operator=(const Game&);

	public:
		bool GameOn;
		float speed_tank, speed_bullet;

		static Game& Instance();
		
		void wait_clients();
		void start_game();
		void create_tanks(std::vector<sf::Vector2<float>> points);
		void destroy_tank(unsigned id);
		void end_game();
		//void ImportToGame(int key_tank, int key_bullet, unsigned id);
		void ImportToGame(int key, unsigned id);
};