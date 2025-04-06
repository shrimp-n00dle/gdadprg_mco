#include "FontManager.hpp"


FontManager* FontManager::sharedInstance = NULL;

/**
 * Returns the singleton instance of FontManager, creating it if it doesn't exist
 * @return Pointer to the FontManager instance
 */
FontManager* FontManager::getInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new FontManager();
	}
	return sharedInstance;
}

/**
 * Loads all default fonts into the manager
 * Includes default, nesfont, and oldnesfont
 */
void FontManager::loadAll()
{
	loadFont("default","Assets/UI/Sansation.ttf");
	loadFont("nesfont", "Assets/UI/nes2.ttf");
	loadFont("oldnesfont", "Assets/UI/nes.ttf");
}

/**
 * Loads a single font file into the manager
 * @param key Unique identifier for the font
 * @param path File path to the font file
 */
void FontManager::loadFont(std::string key,std::string path)
{
	sf::Font* font = new sf::Font();
	font->loadFromFile(path);
	fontMap[key] = font;
}

/**
 * Gets a font from the manager
 * @param key Unique identifier of the font to retrieve
 * @return Pointer to the font, or nullptr if not found
 */
sf::Font* FontManager::getFont(std::string key)
{
	if (fontMap[key] != NULL)
	{
		return fontMap[key];
	}

	else
	{
		std::cout << "No font found for " << key;
		return NULL;
	}
}