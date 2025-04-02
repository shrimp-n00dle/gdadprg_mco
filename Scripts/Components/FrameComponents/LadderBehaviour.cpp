#include "LadderBehaviour.hpp"

LadderBehaviour::LadderBehaviour(std::string name) : AComponent(name, Script)
{
	initializeSprites();
}

void LadderBehaviour::perform()
{
	Player* frameObj = (Player*)this->getOwner();

	//If the current sprite is equal to climb_sheet
	if (frameObj->getSheetName() == "climb_sheet")
	{
		MCOPlayerInput* frameInputController = (MCOPlayerInput*)(frameObj->getComponentsOfType(ComponentType::Input)[0]);
		sf::Transformable* frameTransformable = frameObj->getTransformable();

		/*Checkers*/
		if (frameTransformable == nullptr) std::cout << "frameTransformable not found" << std::endl;
		if (frameInputController == nullptr)  std::cout << "frameInputController not found" << std::endl;


		if (frameObj->bLadder)
		{
			if (frameInputController->isDown())
			{
				counter--;

			}
			else if (frameInputController->isUp())
			{
				counter++;
			}
		}

		if (frameObj->bLadder == false && frameObj->bHammer == false) frameObj->changeSpriteState("walk_sheet");


		/*if its a negative number, or is beyond 38 go to the beginning of the list and set coutner to 0 or 38*/
		if (counter > 3) counter = 0;
		else if (counter < 0) counter = 3;

		coord = traverseList(counter);

		/*Sprite Rendering*/
		currSprite = sf::IntRect(coord[0], coord[1], coord[2], coord[3]);
		frameObj->frameSprite->setTextureRect(currSprite);
		frameObj->frameSprite->setOrigin(currSprite.width / 2.0f, currSprite.height / 2.0f);
	}
	
}

void LadderBehaviour::initializeSprites()
{
	//1. Parse a JSON file
	FILE* file = fopen("Assets/MCOAssets/SpriteSheet/Climb/Climb.json", "rb");

	//2. Check if we opened succesfully
	assert(file != 0);

	char readBuffer[65536];
	rapidjson::FileReadStream is(file, readBuffer, sizeof(readBuffer));
	rapidjson::Document doc;

	//3. Parse data here
	doc.ParseStream(is);
	fclose(file);

	//4. Read the data
	assert(doc.IsObject());

	rapidjson::Value& player = doc["frames"];
	assert(player.IsObject());

	std::vector<int> coords;
	int counter = 0;

	//accessing all the names and storing the values
	for (auto& m : player.GetObject())
	{
		//std::cout << m.name.GetString() << "\n";

		for (auto& p : player[m.name.GetString()]["frame"].GetObject())
		{
			coords.push_back(p.value.GetInt());
		}
		spriteList.insert({ counter,coords });

		/*Clear and go to next object*/
		coords.clear();
		counter++;

	}
	coord = { 0,0,19,20};
}

std::vector<int> LadderBehaviour::traverseList(int counter)
{
	auto i = spriteList.find(counter)->second;
	return i;
}

