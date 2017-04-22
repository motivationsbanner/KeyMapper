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
				std::cout << "Shoolult" << std::endl;
        }
		
		

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
};


// #include <iostream>
// #include <fstream>
// #include <SFML/Window.hpp>
// #include <SFML/Graphics.hpp>
 
// enum InputType
// {
    // KeyboardInput,
    // MouseInput,
    // JoystickInput
// };
 
// struct MyKeys
// {
    // InputType myInputType;
    // sf::Event::EventType myEventType;
    // sf::Keyboard::Key myKeyCode;
    // sf::Mouse::Button myMouseButton;
// };
 
// bool TestEvent(MyKeys k, sf::Event e);
// void Shoot(void);
// void Jump(void);
 
// int main(int argc, char** argv)
// {
    // // Variables for main
    // sf::RenderWindow App;
    // bool Running = true;
    // sf::Event Event;
 
    // // Variables for demo
    // std::map<std::string,MyKeys> Keys;
    // MyKeys key;

    // // Let's bind the left mouse button to the "Shoot" action
    // key.myInputType = MouseInput;
    // key.myEventType = sf::Event::MouseButtonPressed;
    // key.myMouseButton = sf::Mouse::Left;
    // Keys["Shoot"] = key;
	
	// std::cout << Keys["Shoot"].myInputType << std::endl;

    // // Let's bind the Return key to the "Jump" action
    // key.myInputType = KeyboardInput;
    // key.myEventType = sf::Event::KeyPressed;
    // key.myKeyCode = sf::Keyboard::Return;
    // Keys["Jump"] = key;

    // // Let's bind the Left Control key to the "Use" action
    // key.myInputType = KeyboardInput;
    // key.myEventType = sf::Event::KeyPressed;
    // key.myKeyCode = sf::Keyboard::LControl;
    // Keys["Use"] = key;
 
    // // Window creation
    // App.create(sf::VideoMode(640, 480, 16), "config test");
 
    // // Main loop
    // while (Running)
    // {
        // // Manage Events
        // while (App.pollEvent(Event))
        // {
            // // Using Event normally
 
            // // Window closed
            // if (Event.type == sf::Event::Closed)
            // {
                // Running = false;
            // }
 
            // // Key pressed
            // if (Event.type == sf::Event::KeyPressed)
            // {
                // switch (Event.key.code)
                // {
                    // case sf::Keyboard::Escape :
                        // Running = false;
                        // break;
                    // case sf::Keyboard::A :
                        // std::cout << "Key A !" << std::endl;
                        // break;
                    // default :
                        // break;
                // }
            // }
 
            // // Using Event for binding
            // // Shoot
            // if (TestEvent(Keys["Shoot"], Event))
            // {
                // // You can use a function
                // Shoot();
            // }
            // if (TestEvent(Keys["Jump"], Event))
            // {
                // Jump();
            // }
            // if (TestEvent(Keys["Use"], Event))
            // {
                // // or only code
                // std::cout << "Use !" << std::endl;
            // }
        // }
 
        // // Display the result
        // App.display();
    // }
 
    // // End of application
    // return EXIT_SUCCESS;
// }
 
// bool TestEvent(MyKeys k, sf::Event e)
// {
    // // Mouse event
    // if (k.myInputType == MouseInput &&
        // k.myEventType == e.type &&
        // k.myMouseButton == e.mouseButton.button)
    // {
        // return (true);
    // }
    // // Keyboard event
    // if (k.myInputType == KeyboardInput &&
        // k.myEventType == e.type &&
        // k.myKeyCode == e.key.code)
    // {
        // return (true);
    // }
    // return (false);
// }
 
// void Shoot(void)
// {
    // std::cout << "Shoot !" << std::endl;
// }
 
// void Jump(void)
// {
    // std::cout << "Jump !" << std::endl;
// }