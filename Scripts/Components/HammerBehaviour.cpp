#include "HammerBehaviour.hpp"

HammerBehaviour::HammerBehaviour(std::string name) : AComponent(name, Script) { }

void HammerBehaviour::perform()
{
	ticks += deltaTime.asSeconds();
	Player* player = (Player*)this->getOwner();
	sf::Transformable* transformable = this->getOwner()->getTransformable();

	if (player->bHammer)
	{
		timer -= deltaTime.asSeconds();
		std::cout << timer << std::endl;

		if (timer <= 0.0f)
		{
			timer = 10.0f;
			player->bHammer = false;
			player->changeSpriteState("walk_sheet");
		}
	}
}

//void HammerBehaviour::configure(float delay)
//{
	//this->delay = delay;
//}