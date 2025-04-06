#include "HammerBehaviour.hpp"

HammerBehaviour::HammerBehaviour(std::string name) : AComponent(name, Script)
{
	this->initializeSprites();
}
void HammerBehaviour::perform()
{
	Player* frameObj = (Player*)this->getOwner();
	MCOPlayerInput* frameInputController = (MCOPlayerInput*)(frameObj->getComponentsOfType(ComponentType::Input)[0]);
	sf::Transformable* transformable = this->getOwner()->getTransformable();

	if (frameObj->bHammer && frameObj->getSheetName() == "hammer_sheet")
	{
		timer -= deltaTime.asSeconds();
		//std::cout << timer << std::endl;

		if (frameInputController->isLeft())
		{
			counter--;
			frameInputController->setLeft(false);
		}
		else if (frameInputController->isRight())
		{
			counter++;
			frameInputController->setRight(false);
		}
		if (timer <= 0.0f)
		{
			timer = 10.0f;
			frameObj->bHammer = false;
			frameObj->changeSpriteState("walk_sheet");
			
		}

		/*add hammer music*/
		//if its currenlty playing dont play it again
		if (SFXManager::getInstance()->mAudioList[0]->getSong()->getStatus() != 2)SFXManager::getInstance()->mAudioList[0]->playSong();

		

		/*if its a negative number, or is beyond 38 go to the beginning of the list and set coutner to 0 or 38*/
		if (counter > 5) counter = 0;
		else if (counter < 0) counter = 5;

		coord = traverseList(counter);

		/*Sprite Rendering*/
		currSprite = sf::IntRect(coord[0], coord[1], coord[2], coord[3]);
		frameObj->frameSprite->setTextureRect(currSprite);
		frameObj->frameSprite->setOrigin(currSprite.width / 2.0f, currSprite.height / 2.0f);
	}
}


void HammerBehaviour::initializeSprites()
{
	//1. Parse a JSON file
	FILE* file = fopen("Assets/MCOAssets/SpriteSheet/Hammer/Hammer.json", "rb");

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
	//"frame": {"x":0,"y":0,"w":14,"h":31},
	coord = { 0,0,14,31 };
	//coord = traverseList(0);
}

std::vector<int> HammerBehaviour::traverseList(int counter)
{
	auto i = spriteList.find(counter)->second;
	return i;
}