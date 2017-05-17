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
	FILE* config = fopen("KeyMapper.config", "r+");

	int eventType, inputType, keyCode, modifier;
	char keyName[20];

	/* Load from File and add to Keys Map */
	while (fscanf(config, "%s %i, %i, %i, %i", &keyName, &eventType, &inputType, &keyCode, &modifier) == 5)
	{
		if (keyName == key)
		{
			/* Update Key */
			Key updatedKey = this->Keys[key];

			/* Check for MouseButton */
			if (e.type == sf::Event::EventType::MouseButtonPressed)
			{
				updatedKey.eventType = e.type;
				updatedKey.inputType = MouseInput;
				updatedKey.mouseButton = e.mouseButton.button;
			}

			/* Check for KeyPressed*/
			if (e.type == sf::Event::EventType::KeyPressed)
			{
				/* Ignore Modifier Keys */
				if (e.key.code == sf::Keyboard::Key::LShift ||
					e.key.code == sf::Keyboard::Key::LControl ||
					e.key.code == sf::Keyboard::Key::LAlt) continue;

				updatedKey.eventType = e.type;
				updatedKey.inputType = KeyboardInput;
				updatedKey.keyCode = e.key.code;

				/* Set Modifier */
				if (e.key.alt) updatedKey.modifier = sf::Keyboard::Key::LShift;
				else if (e.key.control) updatedKey.modifier = sf::Keyboard::Key::LControl;
				else if (e.key.alt) updatedKey.modifier = sf::Keyboard::Key::LAlt;
			}

			this->Keys[keyName] = updatedKey;

			/* Update Setting File */
		}
	}
	fclose(config);

	return false;
}


/* 
	Open Points:
	
	- Key is already bound to something
	- How do I want to bind Modifier Keys

*/

