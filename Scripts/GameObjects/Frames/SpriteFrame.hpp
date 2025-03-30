#pragma once
#include "../AGameObject.hpp"
#include "../../Managers/TextureManager.hpp"
#include "../../Renderer/Renderer.hpp"
#include "../../Managers/GameObjectManager.hpp"
#include "../../Inputs/FrameInput.hpp"
#include "../../Components/FrameComponents/FrameSwticher.hpp"
#include "../../Components/MCOPlayerMovement.hpp"
#include "../../Inputs/MCOPlayerInput.hpp"


class SpriteFrame : public AGameObject
{
public:
	SpriteFrame(std::string name);

	void initialize();

	sf::Sprite* frameSprite;

};



