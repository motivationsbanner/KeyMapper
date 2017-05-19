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
public:  
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
    
    /// <summary>
    /// Starts the Keybind process
    /// </summary>
    void Start();
        
    /// <summary>
    /// Applies the Keybinds created during the Keybind process.
    /// </summary>
    void Apply();
    
    /// <summary>
    /// Discards the Keybinds created during the Keybind process.
    /// </summary>
    void Discard();
    
    /// <summary>
    /// Gets the bind mode. 
    /// </summary>
    /// <returns><c>true</c> if the binding process has started; otherwise, <c>false</c></returns>
    bool GetBindMode();
        
    /// <summary>
    /// Check if there are duplicate Keys or not.
    /// </summary>
    /// <returns></returns>
    bool GetDuplicatedKeys();
    
    /// <summary>
    /// Get the keys with Actionname and the Keybind
    /// </summary>
    /// <returns></returns>
    std::map<std::string, std::string> GetKeys();

private:

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
        Key() : modifier(sf::Keyboard::Unknown) { };
        InputType inputType;
        sf::Event::EventType eventType;
        sf::Keyboard::Key keyCode;
        sf::Mouse::Button mouseButton;
        sf::Keyboard::Key modifier;
    };

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
    
    /// <summary>
    /// Map for the Key and the Keyaction Name ("Jump")
    /// </summary>
    std::map<std::string, KeyMapper::Key> Keys;

    /// <summary>
    /// Save Keybinds before applying them
    /// </summary>
    std::map<std::string, KeyMapper::Key> SaveKeys;
    
    /// <summary>
    /// If a binding process is started and Keybinding is possible
    /// </summary>
    bool BindMode = false;
    
    /// <summary>
    /// If there are Duplicate Keys or not
    /// </summary>
    bool DuplicateKeys = false;

    /// <summary>
    /// Check if there are Dublicate Keys.
    /// </summary>
    /// <returns></returns>
    bool CheckDuplicateKeys();

    /// <summary>
    /// Compares two Keys.
    /// </summary>
    /// <param name="key1">The first key.</param>
    /// <param name="secondKey">The second key</param>
    /// <returns></returns>
    bool CompareKey(KeyMapper::Key firstKey, KeyMapper::Key secondKey);
    
    /// <summary>
    /// Gets the name of the key.
    /// </summary>
    /// <param name="key">The key.</param>
    /// <returns></returns>
    const char* getKeyName(const sf::Keyboard::Key key);
    
    /// <summary>
    /// Gets the name of the mouse button.
    /// </summary>
    /// <param name="button">The button.</param>
    /// <returns></returns>
    const char* KeyMapper::getMouseName(const sf::Mouse::Button button);
};