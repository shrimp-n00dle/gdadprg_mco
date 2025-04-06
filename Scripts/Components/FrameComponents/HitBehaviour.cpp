#include "HitBehaviour.hpp"

HitBehaviour::HitBehaviour(std::string name) : AComponent(name, Script)
{
	initializeSprites();
}

void HitBehaviour::perform()
{
	Player* frameObj = (Player*)this->getOwner();
	MCOPlayerInput* frameInputController = (MCOPlayerInput*)(frameObj->getComponentsOfType(ComponentType::Input)[0]);
	sf::Transformable* frameTransformable = frameObj->getTransformable();

	if (frameObj->getSheetName() == "hit_sheet")
	{
		if (loop >= 2) 
		{
			coord = traverseList(4);
		}
		else if (frameObj->hitTimer <= 0.0f)
		{
				counter++;
				frameObj->hitTimer = 0.2f;
				/*if its a negative number, or is beyond 38 go to the beginning of the list and set coutner to 0 or 38*/
				if (counter > 3) { counter = 0; loop++; }
				else if (counter < 0)
				{
					counter = 2;
				}
				coord = traverseList(counter);
	
		}
		
		/*Sprite Rendering*/
		currSprite = sf::IntRect(coord[0], coord[1], coord[2], coord[3]);
		frameObj->frameSprite->setTextureRect(currSprite);
		frameObj->frameSprite->setOrigin(currSprite.width / 2.0f, currSprite.height / 2.0f);
	}

}

void HitBehaviour::initializeSprites()
{
	//1. Parse a JSON file
	FILE* file = fopen("Assets/MCOAssets/SpriteSheet/Hit/Hit.json", "rb");

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

	//	"frame": {"x":0,"y":0,"w":18,"h":18},
	coord = { 0,0,18,18};
	//currSprite = sf::IntRect(0, 0, 150, 84);
}

std::vector<int> HitBehaviour::traverseList(int counter)
{
	auto i = spriteList.find(counter)->second;
	return i;
}

