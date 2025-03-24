#include "BGMovement.hpp"

BGMovement::BGMovement(std::string name) : AComponent(name, Script) 
{
	
}

void BGMovement::perform()
{

	BGameObject* bgObj = (BGameObject*)getOwner();
	sf::Transformable* bgTransformable = bgObj->getTransformable();

	if (bgTransformable == nullptr)
	{
		std::cout << "bgTransformable not found" << std::endl;
	} 

	/*make Bg scroll slowly*/
	sf::Vector2f offset(0.0f, 0.0f);
	offset.y += SPEED_MULTIPLIER;
	bgObj->getTransformable()->move(offset * deltaTime.asSeconds());

	sf::Vector2f localPos = bgObj->getTransformable()->getPosition();
	if (localPos.y * deltaTime.asSeconds() > 0)
	{
		/*reset position*/
		bgObj->getTransformable()->setPosition(0, -480 * 7);
	}
}
