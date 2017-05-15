#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "KeyMapper.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	
	auto mapper = new KeyMapper();
	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			
			if (mapper->KeyPressed("Shoot", event))
				std::cout << "Shoot" << std::endl;
			if (mapper->KeyPressed("Up", event))
				std::cout << "Up" << std::endl;
			if (mapper->KeyPressed("Down", event))
				std::cout << "Down" << std::endl;
			if (mapper->KeyPressed("Left", event))
				std::cout << "Left" << std::endl;
			if (mapper->KeyPressed("Right", event))
				std::cout << "Right" << std::endl;
			if (mapper->KeyPressed("Exit", event))
				return EXIT_SUCCESS;
        }
		
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
};
