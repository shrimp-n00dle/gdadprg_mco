#pragma once
#include "../AGameObject.hpp"
#include "../Listeners/ButtonListener.hpp"
#include "../../Inputs/UIButtonInput.hpp"
#include "../../Managers/ApplicationManager.hpp"

class UIButton : public AGameObject
{
public:
	UIButton(std::string name, sf::Texture* normalTexture, sf::Texture* pressedTexture);
	void initialize();

	void changeButtonToNormal();
	void changeButtonToPressed();
	sf::FloatRect getLocalBounds();
	sf::FloatRect getGlobalBounds();
	void setButtonListener(ButtonListener* listener);
private:
	sf::Texture* normalTexture;
	sf::Texture* pressedTexture;
	sf::Sprite* sprite;
	ButtonListener* listener;
};

