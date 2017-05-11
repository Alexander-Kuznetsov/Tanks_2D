#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>

#include "map.h"
#include "tank.h"
#include "errors.h"
#include "network.h"
#include "interface.h"


#include <iostream>
#include <string>

int main(){
	sf::RenderWindow window(sf::VideoMode(480, 512), "Tanks 2D");
	window.display();

	Network network;
	if (network.connect_to_server() == ConnectError)
		return ConnectError;
	
	Interfaces interfaces;

    while (window.isOpen()) {
        sf::Event event;

        // Flags for key pressed
        bool upFlag = false;
        bool downFlag = false;
        bool leftFlag = false;
        bool rightFlag = false;	

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                // If escape is pressed, close the application
                    case  sf::Keyboard::Escape : 
						window.close(); 
                        break;
                // Process the up, down, left and right keys
                    case sf::Keyboard::Up : 
                        upFlag=true;
						network.PushInPacket(Up);
						network.SendPacket();
                        break;
                    case sf::Keyboard::Down : 
                        downFlag=true;
						network.PushInPacket(Down);
						network.SendPacket();
                        break;
                    case sf::Keyboard::Left : 
                        leftFlag=true; 
						network.PushInPacket(Left);
						network.SendPacket();
                        break;
                    case sf::Keyboard::Right : 
                        rightFlag=true; 
						network.PushInPacket(Right);
						network.SendPacket();
                        break;
					
					case sf::Keyboard::Space :
						network.PushInPacket(Space);
						network.SendPacket();
                    default : break;
                }
            }

            // If a key is released
            if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                // Process the up, down, left and right keys
                    case sf::Keyboard::Up : 
                        upFlag=false; 
                        break;
                    case sf::Keyboard::Down: 
                        downFlag=false; 
                        break;
                    case sf::Keyboard::Left: 
                        leftFlag=false; 
                        break;
                    case sf::Keyboard::Right: 
                        rightFlag=false; 
                        break;
                    default : break;
                }
            }
        }

		network.ClearOutPacket();

		window.clear();

		network.ReceivePacket();

		unsigned count_tanks;
		interfaces.DrawInterface(window, 15, 100);
		network.ReadDataFromPacket(window);
		
       
        window.display();
		network.ClearInPacket();
    }

    return 0;
}
