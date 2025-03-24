#pragma once
#include "BGameObject.hpp"

BGameObject::BGameObject(std::string name) : AGameObject(name)
{
	this->name = name;
}

void BGameObject::initialize()
{
	/*Assign Texture*/
	sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("desert_bg"));
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();

	/*make BG height x k  to emulate repeating BG*/
	sprite->setTextureRect(sf::IntRect(0,0,640,480 * 8));

	Renderer* renderer = new Renderer("BgImage");
	renderer->assignDrawable(sprite);
	attachComponent(renderer);

	BGMovement* bgMove = new BGMovement("bgMovement");
	this->attachComponent(bgMove);
}

void BGameObject::processInput(sf::Event event) {}



