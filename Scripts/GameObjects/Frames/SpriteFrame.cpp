#include "SpriteFrame.hpp"

SpriteFrame::SpriteFrame(std::string name) : AGameObject(name) 
{
}

void SpriteFrame::initialize()
{
	//sf::Sprite* sprite = new sf::Sprite();
	frameSprite = new sf::Sprite();
	frameSprite->setTexture(*TextureManager::getInstance()->getTexture("sprite_sheet"));
	sf::Vector2u textureSize = frameSprite->getTexture()->getSize();

	Renderer* renderer = new Renderer("SpriteFrame");
	renderer->assignDrawable(frameSprite);
	attachComponent(renderer);

	setChildPosition(300/2, 300/2);

	//Attach Input and behvaiour below
	FrameInput* spriteInput = new FrameInput("frameInput");
	this->attachComponent(spriteInput);

	FrameSwitcher* switcher = new FrameSwitcher("frameSwitcher");
	this->attachComponent(switcher);
}


