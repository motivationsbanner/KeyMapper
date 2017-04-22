#include "KeyMapper.h"

#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

KeyMapper::KeyMapper() 
{
	Key key;
	// init Keys etc
	key.inputType = MouseInput;
	key.eventType = sf::Event::MouseButtonPressed;
	key.mouseButton = sf::Mouse::Left;
	this->Keys["Shoot"] = key; // this part is working
}

KeyMapper::~KeyMapper()
{
  // destroy stuff
}

bool KeyMapper::KeyPressed(std::string key, sf::Event e)
{
	Key k = this->Keys[key];

	// mouse event
	if (k.inputType == MouseInput &&
		k.eventType == e.type &&
		k.mouseButton == e.mouseButton.button)
	{
		return true;
	}

	// keyboard event
	if (k.inputType == KeyboardInput &&
		k.eventType == e.type &&
		k.keyCode == e.key.code)
	{
		return true;
	}
	return false;
}
