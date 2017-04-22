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
        }
		
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
};
