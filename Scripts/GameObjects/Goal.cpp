#include "Goal.hpp"

/**
 * Constructor for Goal object
 * @param name Name identifier for the goal object
 */
Goal::Goal(std::string name) : AGameObject(name)
{
}

/**
 * Initializes the goal object
 * Creates a collider for the goal area and sets up debug visualization
 */
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

/**
 * Called when a collision with another object begins
 * @param object The object that collided with the goal
 */
void Goal::onCollisionEnter(AGameObject* object)
{}

/**
 * Called when a collision with another object ends
 * @param object The object that stopped colliding with the goal
 */
void Goal::onCollisionExit(AGameObject* object)
{
    // No special handling needed when player leaves the goal area
}
