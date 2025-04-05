#pragma once
#include "../AGameObject.hpp"
#include "../../Managers/TextureManager.hpp"
#include "../../Game.hpp"
#include "../../Renderer/Renderer.hpp"
#include "../../Managers/GameObjectManager.hpp"
#include "../Listeners/ButtonListener.hpp"
#include "UIButton.hpp"
#include "../Listeners/CollisionListener.hpp"
#include "ResultScreen.hpp"

#include "iostream"
#include "string"

class JScene;
class Level1Map : public AGameObject, public CollisionListener
{
public:
	Level1Map(std::string name);

	void initialize();
	void onCollisionEnter(AGameObject* object);
	void onCollisionExit(AGameObject* object);

private:
	bool debugMode = true; // Set to true for visualizing colliders
	std::vector<sf::RectangleShape> debugRects;
	ResultScreen* resultScreen;
	bool levelCompleted = false;
};

