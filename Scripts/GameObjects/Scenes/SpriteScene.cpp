#include "SpriteScene.hpp"

SpriteScene::SpriteScene() : AScene("SpriteScene") {};

void SpriteScene::onLoadResources() {};

void SpriteScene::onLoadObjects() 
{
	SpriteFrame* frame = new SpriteFrame("spriteFrame");
	this->registerObject(frame);

};
void SpriteScene::onUnloadResources() {};



