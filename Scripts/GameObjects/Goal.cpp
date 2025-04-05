#include "Goal.hpp"

Goal::Goal(std::string name) : AGameObject(name)
{
}

void Goal::initialize()
{
    // Create a collider for the goal area
    Collider* goalCollider = new Collider("GoalCollider");
    goalCollider->setLocalBounds(sf::FloatRect(264, 167, 144, 7));
    goalCollider->setCollisionListener(this);
    this->attachComponent(goalCollider);
    PhysicsManager::getInstance()->trackObject(goalCollider);

    // Debug visualization of the goal area
    sf::RectangleShape* goalArea = new sf::RectangleShape();
    goalArea->setPosition(264, 167);
    goalArea->setSize(sf::Vector2f(144, 7));
    goalArea->setFillColor(sf::Color(255, 255, 0, 100)); // YELLOWWWWW!
    goalArea->setOutlineColor(sf::Color::Yellow);
    goalArea->setOutlineThickness(2);

    /*
    Renderer* goalRenderer = new Renderer("GoalArea");
    goalRenderer->assignDrawable(goalArea);
    this->attachComponent(goalRenderer);
    */
}

void Goal::onCollisionEnter(AGameObject* object)
{}

void Goal::onCollisionExit(AGameObject* object)
{
    // No special handling needed when player leaves the goal area
}
