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

class ResultScreen : public AGameObject, public ButtonListener
{
private:
    UIText* scoreText;
    UIText* bonusText;
    UIText* totalText;

public:
    ResultScreen(std::string name);

    void initialize();
    void updateScoreDisplay();
    void setEnabled(bool flag) override;

    void onButtonClick(UIButton* button);
    void onButtonReleased(UIButton* button);
}; 