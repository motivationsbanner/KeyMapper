#pragma once

#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/// <summary>
/// Allows the Mapping of Keynames and Keys, loaded and saved to the KeyMapper Config File
/// </summary>
class KeyMapper
{	
private:	
	/// <summary>
	/// The last Key pressed
	/// </summary>
	sf::Keyboard::Key lastKey = sf::Keyboard::Key::Unknown;
	
	/// <summary>
	/// Determines whether the specified key is modifier.
	/// </summary>
	/// <param name="key">The key.</param>
	/// <returns>
	///   <c>true</c> if the specified key is a modifier; otherwise, <c>false</c>.
	/// </returns>
	bool IsModifier(sf::Keyboard::Key key);

public: 
	/// <summary>
	/// InputType Enum
	/// </summary>
	enum InputType
	{
		KeyboardInput,
		MouseInput,
		JoystickInput	
	};
  
	/// <summary>
	/// Key Structure
	/// </summary>
	struct Key
	{
		Key(): modifier(sf::Keyboard::Unknown) { };
		InputType inputType;
		sf::Event::EventType eventType;
		sf::Keyboard::Key keyCode;
		sf::Mouse::Button mouseButton;
		sf::Keyboard::Key modifier;
	};
  
	/// <summary>
	/// Map for the Key and the Keyaction Name ("Jump")
	/// </summary>
	std::map<std::string, Key> Keys;
	
	/// <summary>
	/// Initializes a new instance of the <see cref="KeyMapper"/> class.
	/// </summary>
	KeyMapper();


	/// <summary>
	/// Finalizes an instance of the <see cref="KeyMapper"/> class.
	/// </summary>
	~KeyMapper();
		
	/// <summary>
	/// Check if the Key / Mouse linked to the Keyname is Pressed.
	/// </summary>
	/// <param name="key">The Keyaction name (for Example "Jump").</param>
	/// <param name="e">The Event</param>
	/// <returns>Result of the Evaluation</returns>
	bool KeyPressed(std::string key, sf::Event e);

	/// <summary>
	/// Saves the specified key.
	/// </summary>
	/// <param name="key">The Keyaction name (for Example "Jump").</param>
	/// <param name="e">The Event</param>
	/// <returns>Result of the Save</returns>
	bool Save(std::string key, sf::Event e);
	
	/// <summary>
	/// Writes the Config File.
	/// </summary>
	void WriteFile();
};