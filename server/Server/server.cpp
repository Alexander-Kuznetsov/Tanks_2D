#include <iostream>
#include <sstream>
#include <string>

#include "network.h"
#include "game.h"
#include "errors.h"

int main() {
	Game& game = Game::Instance();
	Network& network = Network::Instance();
	network.max_clients = 1;
	network.port = 2001;

	if (network.listen_port(network.port) == PortNotOpen)
		return PortNotOpen;
	
	game.wait_clients();
	game.start_game();
	game.end_game();

	// system("pause");
	return 0;
}