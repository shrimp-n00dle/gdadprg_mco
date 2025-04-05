#pragma once
#include "../AGameObject.hpp"
#include "../../Managers/TextureManager.hpp"
#include "../../Game.hpp"
#include "../../Renderer/Renderer.hpp"
#include "../../Managers/GameObjectManager.hpp"
#include "../Listeners/ButtonListener.hpp"
#include "UIButton.hpp"
#include "UIText.hpp"
#include "../../Managers/ScoreManager.hpp"

#include "iostream"
#include "string"
#include <sstream>
#include <iomanip>

class Level1UI : public AGameObject, public ButtonListener
{
public:
	Level1UI(std::string name);

	void initialize();

	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
	void update(sf::Time deltaTime);

private:
	void updateScoreDisplay();
	void updateBonusScore(sf::Time deltaTime);

	UIText* playerScoreText;
	UIText* highScoreText;
	UIText* bonusText;
	sf::Time bonusCountdown = sf::Time::Zero;
};

