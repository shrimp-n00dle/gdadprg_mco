#include "AirplaneSupportMovement.hpp"

AirplaneSupportMovement::AirplaneSupportMovement(std::string name) : AComponent(name,Script)
{

}

void AirplaneSupportMovement::perform()
{   
	AirplaneSupport* supObj = (AirplaneSupport*)getOwner();
	if (bReturn) supObj->getTransformable()->move(-1.0f, 0.0f);
	else supObj->getTransformable()->move(1.0f, 0.0f);

	//If the ship is on the right
	if (supObj->getTransformable()->getPosition().x <= -50) bReturn = false;
	////If the ship is on the left
	else if (supObj->getTransformable()->getPosition().x >= 50) bReturn = true;
}
