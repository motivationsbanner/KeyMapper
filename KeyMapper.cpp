#include "KeyMapper.h"

#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

KeyMapper::KeyMapper()
{

	FILE* config = fopen("KeyMapper.config", "r");
	int eventType, inputType, keyCode, modifier;
	char keyName[20];

	while(fscanf(config, "%s %i, %i, %i, %i", &keyName, &eventType, &inputType, &keyCode, &modifier) == 5)
	{
		Key key;
		key.eventType = (sf::Event::EventType) eventType;
		key.inputType = (KeyMapper::InputType) inputType;
		key.keyCode = (sf::Keyboard::Key) keyCode;
		key.modifier = (sf::Keyboard::Key) modifier;

		this->Keys[keyName] = key;
	}	
	fclose(config);
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

