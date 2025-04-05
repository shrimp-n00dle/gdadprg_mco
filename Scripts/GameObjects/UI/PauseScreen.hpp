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

class PauseScreen : public AGameObject, public ButtonListener
{
public:
    PauseScreen(std::string name);

    void initialize();

    void onButtonClick(UIButton* button);
    void onButtonReleased(UIButton* button);
}; 