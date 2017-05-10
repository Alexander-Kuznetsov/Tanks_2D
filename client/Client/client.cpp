#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include "map.h"
#include <iostream>
#include <string>

enum TurnObject {
	Up = 100,
	Down = 101,
	Left = 102,
	Right = 103,
	Space = 104
};

class Bullet {
	public:
		sf::Vector2<float> point;
		TurnObject turn;

		Bullet::Bullet (float x, float y, TurnObject turn):
			point(x, y),
			turn(turn)
		{ }
};

class Tank{
	public:
		int HP;
		sf::Vector2<float> point;
		std::vector<Bullet> bullets;
		TurnObject turn;
		
		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;

		Tank::Tank (int health = 0, float x = 0, float y = 0, TurnObject turn = TurnObject::Up): 
			HP(health), 
			point(x, y),
			turn(turn)
		{
			image.loadFromFile("../Data/Images/tank_top.png");
			texture.loadFromImage(image); 
			sprite.setTexture(texture);
			sf::FloatRect spriteSize = sprite.getLocalBounds();
			//size_x = spriteSize.width;
			//size_y = spriteSize.height;
			sprite.setOrigin(spriteSize.width/2.0, spriteSize.height - spriteSize.width/2.0);
			sprite.setScale(0.2, 0.2);
			sprite.setPosition(x, y);
		}
};


int main(){

	sf::RenderWindow window(sf::VideoMode(500, 500), "Tanks 2D");
    //sf::Image tank;
   // tank.loadFromFile("../images/player1.png");

	sf::Image map_image;//объект изображения для карты
	map_image.loadFromFile("../Data/Images/map.png");//загружаем файл для карты
	sf::Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	sf::Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//з

	sf::Image interfaces_image;//объект изображения для карты
	interfaces_image.loadFromFile("../Data/Images/interface.png");//загружаем файл для карты
	sf::Texture interfaces;//текстура карты
	interfaces.loadFromImage(interfaces_image);//заряжаем текстуру картинкой
	sf::Sprite s_interfaces;//создаём спрайт для карты
	s_interfaces.setTexture(interfaces);//з

	sf::Font font;//шрифт 
	font.loadFromFile("../Data/Fonts/CyrilicOld.ttf");
	sf::Text text("", font, 16);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);

    //sf::Texture texture;
    //texture.loadFromImage(tank);
    //texture.setSmooth(true);

    //sf::Sprite sprite;
    //sprite.setTexture(texture);
    //sf::FloatRect spriteSize = sprite.getGlobalBounds();
    //sprite.setOrigin(spriteSize.width/2.0, spriteSize.height /2.0);
	//sprite.setOrigin(16, 16);
    //sprite.setScale(0.2,0.2);
     
	//Tank player = Tank(0, 0, 0)

	sf::TcpSocket socket;
	sf::Packet out_packet, in_packet;

	std::string ip;
	sf::IpAddress server_ip;
	std::cout << "Connect to server, IP address: ";
	
	//"195.19.43.156"
	//192.168.56.1
	std::cin >> ip;
	server_ip = ip.c_str();
	std::cout << server_ip;
	
	sf::Socket::Status status = socket.connect(server_ip, 2001, sf::seconds(15));
	if (status != sf::Socket::Done) {	
		std::cout << std::endl << "Failed connect to the server" << std::endl;
		system("pause");
		return -1;
	}
	else {
		std::cout << std::endl << "You are connected to the server" << std::endl;
		
		out_packet << -1;
		socket.send(out_packet);
		out_packet.clear();

		socket.receive(in_packet);
		//in_packet >> player.point.x >> player.point.y >> player.HP;
		in_packet.clear();
	}

	

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
            while (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                // If escape is pressed, close the application
                    case  sf::Keyboard::Escape : 
						window.close(); 
                        break;
                // Process the up, down, left and right keys
                    case sf::Keyboard::Up : 
                        upFlag=true;
						out_packet << Up;
						out_packet << -1;
                        break;
                    case sf::Keyboard::Down : 
                        downFlag=true;
						out_packet << Down;
						out_packet << -1;
                        break;
                    case sf::Keyboard::Left : 
                        leftFlag=true; 
						out_packet << Left;
						out_packet << -1;
                        break;
                    case sf::Keyboard::Right : 
                        rightFlag=true; 
						out_packet << Right;
						out_packet << -1;
                        break;
					
					case sf::Keyboard::Space :
						if (out_packet.getDataSize() < sizeof(int))
							out_packet << -1;
						out_packet << Space;
                    default : break;
                }
				/*out_packet << 1;
				socket.send(out_packet);
				out_packet.clear();
				sprite.setPosition(player.point.x, player.point.y);

				std::cout << sprite.getPosition().x << "    " << sprite.getPosition().y << std::endl;*/		
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

        /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (sprite.getRotation() != 270) {
                sprite.setRotation(270);
            } 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

            if (sprite.getRotation() != 90) {
                sprite.setRotation(90);
            } 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

            if (sprite.getRotation() != 0) {
                sprite.setRotation(0);
            } 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

            if (sprite.getRotation() != 180) {
                sprite.setRotation(180);
            }
        }*/

		socket.send(out_packet);
		out_packet.clear();

		socket.receive(in_packet);

		int id;
		unsigned size;
		float x, y;
		in_packet >> id;
		in_packet >> size;
		std::cout << id << "    " << size << std::endl;
		std::vector<Tank> tanks;
		for (int i = 0; i < size; i++){
			in_packet >> x;
			in_packet >> y;
			Tank player = Tank(100, x, y, TurnObject::Up);
			tanks.push_back(player);
		}


        window.clear();
		
		for (int i = 0; i < WIDTH_MAP; i++){
			if (i == 0)
				s_interfaces.setTextureRect(sf::IntRect(0, 0, 32, 32));
			else if (i == WIDTH_MAP - 1)
				s_interfaces.setTextureRect(sf::IntRect(64, 0, 32, 32));
			else
				s_interfaces.setTextureRect(sf::IntRect(32, 0, 32, 32));
			s_interfaces.setPosition(i * 32, 0);
			window.draw(s_interfaces);
		}
		text.setString("HP: " + std::to_string(tanks[id].HP));
		text.setPosition(10, 5);
		window.draw(text);

		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++){
				if (Maps[i][j] == '0') 
					s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
				if (Maps[i][j] == '1') 
					s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
				s_map.setPosition(j * 32, (i + 1) * 32);
				window.draw(s_map);
			}

		for (int i = 0; i < size; i++){
			window.draw(tanks[i].sprite);
		}
		
       
        window.display();
		in_packet.clear();
    }
    return 0;
}
