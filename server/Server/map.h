#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "errors.h"

class Map {
	public:
		//real size (width * size(image)) !!!
		unsigned WIDTH;
		unsigned HEIGHT;

		std::vector<std::string> map;
		std::vector<sf::Vector2<float>> PlayerPoints;

		Error LoadMap(unsigned &max_clients);

	private: 

		void read_players(unsigned &max_clients, std::ifstream &fmap);
		void read_map(std::ifstream &fmap);
};