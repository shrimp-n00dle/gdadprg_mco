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

	/*If the current sheet is the hammer sheet, continue
	If not, ignore the condition*/
	if (frameObj->bHammer && frameObj->getSheetName() == "hammer_sheet")
	{
		/*A timer is added so the frames can have an offset before calling the next one*/
		timer -= deltaTime.asSeconds();

		if (frameObj->hammerTimer <= 0.0f)
		{
			counter++;
			frameObj->hammerTimer = 0.2f;

		}
		if (timer <= 0.0f)
		{
			timer = 10.0f;
			frameObj->bHammer = false;
			frameObj->changeSpriteState("walk_sheet");
			
		}

		/*add hammer music*/
		//if its currenlty playing dont play it again
		if (!SFXManager::getInstance()->isSoundPlaying(AudioKeys::HAMMER))
		{
			SFXManager::getInstance()->playSound(AudioKeys::HAMMER);
		}

		

		/*if its a negative number, or is beyond, go to the beginning of the list and set coutner to 0 or the maximum*/
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
	//"frame": {"x":0,"y":0,"w":25,"h":29},
	coord = { 0,0,25,29 };
	//coord = traverseList(0);
}

std::vector<int> HammerBehaviour::traverseList(int counter)
{
	auto i = spriteList.find(counter)->second;
	return i;
}