#include "KeyMapper.h"

#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

bool KeyMapper::IsModifier(sf::Keyboard::Key key)
{
     return (key == sf::Keyboard::Key::LShift ||
        key == sf::Keyboard::Key::LControl ||
        key == sf::Keyboard::Key::LAlt ||
        key == sf::Keyboard::Key::RControl ||	
        key == sf::Keyboard::Key::RShift ||
        key == sf::Keyboard::Key::RAlt);
}

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
        
        /* Load Key Or Mouse */
        if (inputType != KeyMapper::InputType::MouseInput)
            key.keyCode = (sf::Keyboard::Key) keyCode;
        else
            key.mouseButton = (sf::Mouse::Button) keyCode;

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
    auto modifier = k.modifier != sf::Keyboard::Unknown ? (sf::Keyboard::isKeyPressed(k.modifier) || this->lastKey == k.modifier) : true;
     
    /* Handle Mouse Event */
    if (k.inputType == MouseInput &&
        k.eventType == e.type &&
        k.mouseButton == e.mouseButton.button && 
        modifier == true)
    {
        this->lastKey = sf::Keyboard::Unknown;
        return true;
    }

    /* Handle Keyboard Event */
    if (k.inputType == KeyboardInput &&
        k.eventType == e.type &&
        k.keyCode == e.key.code &&
        modifier)
    {
        this->lastKey = sf::Keyboard::Unknown;
        return true;
    }

    /* Handle Modifier */
    if (e.type == sf::Event::EventType::KeyPressed &&
        this->IsModifier(e.key.code))
    {
        this->lastKey = e.key.code;
    }

    return false;
}

bool KeyMapper::Save(std::string key, sf::Event e)
{
    bool success = false;

    /* Update Key */
    Key updatedKey = this->Keys[key];

    /* Check for MouseButton */
    if (e.type == sf::Event::EventType::MouseButtonPressed)
    {
        updatedKey.eventType = e.type;
        updatedKey.inputType = MouseInput;
        updatedKey.mouseButton = e.mouseButton.button;
        updatedKey.modifier = this->lastKey;

        /* Reset last key */
        this->lastKey = sf::Keyboard::Unknown;
        
        success = true;
    }

    /* Check for KeyPressed*/
    if (e.type == sf::Event::EventType::KeyPressed)
    {
        /* Ignore Modifier Keys */
        if (this->IsModifier(e.key.code))
        {
            this->lastKey = e.key.code;
        }

        updatedKey.eventType = e.type;
        updatedKey.inputType = KeyboardInput;
        updatedKey.keyCode = e.key.code;
        updatedKey.modifier = this->lastKey;

        /* Reset last key */
        this->lastKey = sf::Keyboard::Unknown;

        success = true;
    }

    if (success)
        this->Keys[key] = updatedKey;

    return success;
}

void KeyMapper::WriteFile()
{
    FILE* config = fopen("KeyMapper.config", "w");

    for (auto const& x : this->Keys)
    {
        auto value = x.first;
        auto key = x.second;

        /* Save Key Or Mouse */
        int keyCode;
        if (key.inputType != KeyMapper::InputType::MouseInput)
            keyCode = (int)key.keyCode;
        else
            keyCode = (int)key.mouseButton;

        std::string line = (value + " " +
            std::to_string((int)key.eventType) + ", " +
            std::to_string((int)key.inputType) + ", " +
            std::to_string(keyCode) + ", " +
            std::to_string((int)key.modifier));

        const char* c = line.c_str();

        fprintf(config, "%s\n", c);
    }
    fclose(config);
}


/* 
    Open Points:
    
    - Key is already bound to something
    - Exception Handling
    - Must-Have Keys
*/

