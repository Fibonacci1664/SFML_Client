#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

//void testApp()
//{
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        window.draw(shape);
//        window.display();
//    }
//}


int main()
{
	//testApp();

	sf::TcpSocket tcpSocket;
	sf::Time timeout = sf::seconds(10.0f);
	
	sf::Socket::Status socketStatus = tcpSocket.connect("127.0.0.1", 53000, timeout);

	if (socketStatus != sf::Socket::Done)
	{
		std::cout << "Not connected!\n";
	}

	return 0;
}