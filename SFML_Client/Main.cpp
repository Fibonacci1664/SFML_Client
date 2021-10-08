#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

constexpr int MESSAGESIZE = 100;
std::size_t received;
char dataBuffer[MESSAGESIZE];
sf::IpAddress SERVERIP = "127.0.0.1";
unsigned short SERVERPORT = 4444;

void createTCP();
void createUDP();
void testApp();

int main()
{
	//testApp();
    //createTCP();
    createUDP();

	return 0;
}

void createTCP()
{
    // Create TCP
    sf::TcpSocket tcpSocket;
    sf::Time timeout = sf::seconds(10.0f);

    sf::Socket::Status socketStatus = tcpSocket.connect(SERVERIP, SERVERPORT, timeout);

    if (socketStatus != sf::Socket::Done)
    {
        std::cout << "Not connected!\n";
    }

    // Fill buffer with data
    std::string msg;
    std::cin >> msg;
    memset(dataBuffer, '-', MESSAGESIZE);
    memcpy(dataBuffer, msg.c_str(), MESSAGESIZE);

    // Send data
    if (tcpSocket.send(dataBuffer, 100) != sf::Socket::Done)
    {
        std::cout << "Error sending data by TCP!\n";
    }
}

void createUDP()
{
    sf::UdpSocket udpSocket;

    if (udpSocket.bind(SERVERPORT) != sf::Socket::Done)
    {
        std::cout << "UDP bind failed!\n";
    }

    //// To bind a free random port automatically
    //if (udpSocket.bind(sf::Socket::AnyPort) != udpSocket.getLocalPort())
    //{
    //    std::cout << "Random UDP port binding failed!\n";
    //}

    //std::cout << "Random port number assigned: " << udpSocket.getLocalPort();

    // Fill buffer with data
     // Fill buffer with data
    std::cout << "Please send a msg:> ";
    std::string msg;
    std::cin >> msg;
    memset(dataBuffer, '-', MESSAGESIZE);
    memcpy(dataBuffer, msg.c_str(), MESSAGESIZE);

    // Send data
    if (udpSocket.send(dataBuffer, 100, SERVERIP, SERVERPORT) != sf::Socket::Done)
    {
        std::cout << "Error sending data by UDP!\n";
    }
    else
    {
        std::cout << "Msg sent!\n";
    }

    sf::IpAddress serverIP;
    unsigned short serverPort;

    // Receive echo, gets stuck here in block even though the server sends msg?
    if (udpSocket.receive(dataBuffer, 100, received, serverIP, serverPort) != sf::Socket::Done)
    {
        std::cout << "Error receiving UDP echo!\n";
    }

    std::cout << "Received " << received << " bytes from " << SERVERIP << " on port num " << SERVERPORT << '\n';
}

void testApp()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}