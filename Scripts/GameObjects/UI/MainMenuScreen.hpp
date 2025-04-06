#pragma once
#include "../AGameObject.hpp"
#include "../../Managers/TextureManager.hpp"
#include "../../Game.hpp"
#include "../../Renderer/Renderer.hpp"
#include "../../Managers/GameObjectManager.hpp"
#include "../Listeners/ButtonListener.hpp"
#include "UIButton.hpp"

#include "iostream"
#include "string"

class MainMenuScene;

class MainMenuScreen : public AGameObject, public ButtonListener
{
private:
	bool isIntroPlaying = false;
	float introDelay = 0.0f;
	const float INTRO_SOUND_DURATION = 6.0f; // Adjust this based on your intro sound length

public:
	MainMenuScreen(std::string name);

	void initialize();

	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
	void update(sf::Time deltaTime) override;
};

