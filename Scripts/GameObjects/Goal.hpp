#pragma once
#include "AGameObject.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Game.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Managers/GameObjectManager.hpp"
#include "Listeners/CollisionListener.hpp"
#include "UI/ResultScreen.hpp"

class Goal : public AGameObject, public CollisionListener
{
private:
    bool levelCompleted = false;

public:
    Goal(std::string name);
    void initialize();
    void onCollisionEnter(AGameObject* object);
    void onCollisionExit(AGameObject* object);
};

