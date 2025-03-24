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

class ReturnScreen : public AGameObject, public ButtonListener
{
public:
	ReturnScreen(std::string name);

	void initialize();

	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
};

