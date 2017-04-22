#include "KeyMapper.h"

#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

KeyMapper::KeyMapper() 
{
	// init Keys etc
	Key key;
	key.inputType = KeyboardInput;
	key.eventType = sf::Event::KeyPressed;
	key.keyCode = sf::Keyboard::A;
	this->Keys["Shoot"] = key;
}

KeyMapper::~KeyMapper()
{
  // destroy stuff
}

bool KeyMapper::KeyPressed(std::string key, sf::Event e)
{
	Key k = this->Keys[key];
	
	auto modifier = k.modifier != sf::Keyboard::Unknown ? sf::Keyboard::isKeyPressed(k.modifier) : true;
	 
	// mouse event
	if (k.inputType == MouseInput &&
		k.eventType == e.type &&
		k.mouseButton == e.mouseButton.button && 
		modifier == true)
	{
		return true;
	}

	// keyboard event
	if (k.inputType == KeyboardInput &&
		k.eventType == e.type &&
		k.keyCode == e.key.code &&
		modifier)
	{
		return true;
	}
	return false;
}
