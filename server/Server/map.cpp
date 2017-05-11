#include "map.h"

Error Map::LoadMap(unsigned &max_clients) {
	std::ifstream fmap("../Data/Maps/1.txt");
	if (!fmap) {
		std::cerr << "Map not exist!" << std::endl;
		return FileNotExist;
	}
	read_players(max_clients, fmap);
	read_map(fmap);
	fmap.close();
	return Ok;
}

void Map::read_players(unsigned &max_clients, std::ifstream &fmap) {
	std::string tmp;
	std::getline(fmap, tmp);
	std::istringstream buf(tmp);
	buf >> max_clients;
			
	for (unsigned i = 0; i < max_clients; i++) {
		sf::Vector2<float> tmp_points;
		std::getline(fmap, tmp);
		std::istringstream buf(tmp);
		buf >> tmp_points.x;
		buf >> tmp_points.y;
		PlayerPoints.push_back(tmp_points);
	}
}

void Map::read_map(std::ifstream &fmap) {
	std::string tmp;
	std::getline(fmap, tmp);
	std::istringstream buf(tmp);
	buf >> WIDTH;
	buf >> HEIGHT;

	for (unsigned i = 0; i < WIDTH; i++){
		std::string tmp;
		std::getline(fmap, tmp);
		map.push_back(tmp);
	}
}