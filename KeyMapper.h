#pragma once

#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class KeyMapper
{	
public: 
	enum InputType
	{
		KeyboardInput,
		MouseInput,
		JoystickInput	
	};
  
	struct Key
    {
		Key(): modifier(sf::Keyboard::Unknown) { };
		InputType inputType;
    	sf::Event::EventType eventType;
		sf::Keyboard::Key keyCode;
		sf::Mouse::Button mouseButton;
		sf::Keyboard::Key modifier;
	};
  
	std::map<std::string, Key> Keys;
  
	KeyMapper();
	~KeyMapper();

	bool KeyPressed(std::string key, sf::Event e);
};
