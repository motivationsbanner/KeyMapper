#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "KeyMapper.h"

const int movement = 2;

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    bool keybindMode = false;
    /* Init the KeyMapper */
    auto mapper = new KeyMapper();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (!keybindMode)
            {

                if (event.type == sf::Event::Closed)
                    window.close();

                if (mapper->KeyPressed("Shoot", event))
                    std::cout << "Shoot" << std::endl;

                if (mapper->KeyPressed("Up", event))
                {
                    /* Go Up */
                    auto position = shape.getPosition();
                    position.y -= movement;
                    shape.setPosition(position);
                }

                if (mapper->KeyPressed("Down", event))
                {
                    /* Go Down */
                    auto position = shape.getPosition();
                    position.y += movement;
                    shape.setPosition(position);
                }

                if (mapper->KeyPressed("Left", event))
                {
                    /* Go Left */
                    auto position = shape.getPosition();
                    position.x -= movement;
                    shape.setPosition(position);
                }

                if (mapper->KeyPressed("Right", event))
                {
                    /* Go Right */
                    auto position = shape.getPosition();
                    position.x += movement;
                    shape.setPosition(position);
                }

                if (event.key.code == sf::Keyboard::Key::Tab)
                {
                    keybindMode = true;
                }
            }
            else
            {
                keybindMode = !mapper->Save("Right", event);
            }			

            if (mapper->KeyPressed("Exit", event))
            {
                mapper->WriteFile();

                return EXIT_SUCCESS;
            }
                
        }
        
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
};
