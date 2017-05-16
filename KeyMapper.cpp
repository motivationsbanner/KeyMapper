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

	/* Load from File and add to Keys Map */
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

KeyMapper::~KeyMapper() { }

bool KeyMapper::KeyPressed(std::string key, sf::Event e)
{
	Key k = this->Keys[key];
	
	/* sf::Keyboard::Unknown is the Default */
	auto modifier = k.modifier != sf::Keyboard::Unknown ? sf::Keyboard::isKeyPressed(k.modifier) : true;
	 
	/* Handle Mouse Event */
	if (k.inputType == MouseInput &&
		k.eventType == e.type &&
		k.mouseButton == e.mouseButton.button && 
		modifier == true)
	{
		return true;
	}

	/* Handle Keyboard Event */
	if (k.inputType == KeyboardInput &&
		k.eventType == e.type &&
		k.keyCode == e.key.code &&
		modifier)
	{
		return true;
	}

	return false;
}

bool KeyMapper::Save(std::string key, sf::Event e)
{
	return false;
}

