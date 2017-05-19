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

    /* Init the KeyMapper */
    auto mapper = new KeyMapper();
    mapper->GetKeys();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (!mapper->GetBindMode())
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
                    mapper->Start();
                }
            }
            else
            {
                if (event.key.code == sf::Keyboard::Key::Tab)
                    mapper->Discard();

                if (!mapper->Save("Right", event))
                    mapper->Apply();

                if (!mapper->GetBindMode() && mapper->GetDuplicatedKeys())
                    return EXIT_SUCCESS;
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
