#include "KBehaviour.hpp"

KBehaviour::KBehaviour(std::string name) : AComponent(name, Script)
{
	initializeSprites();
}

void KBehaviour::perform()
{
	Kong* frameObj = (Kong*)this->getOwner();

	/*If timer is less than 0 seconds*/
	if (frameObj->timer <= 0.0f)
	{
		counter++;
		if (counter >= 3) counter = 0;
		frameObj->timer = 2.0f;
	}

	coord = traverseList(counter);

	/*Sprite Rendering*/
	currSprite = sf::IntRect(coord[0], coord[1], coord[2], coord[3]);
	frameObj->frameSprite->setTextureRect(currSprite);
	frameObj->frameSprite->setOrigin(currSprite.width / 2.0f, currSprite.height / 2.0f);
}

void KBehaviour::initializeSprites()
{
	//1. Parse a JSON file
	FILE* file = fopen("Assets/MCOAssets/SpriteSheet/Kong/Kong.json", "rb");

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

	//"frame": {"x":0,"y":0,"w":42,"h":34},
	coord = { 0,0,42,24 };
}

std::vector<int> KBehaviour::traverseList(int counter)
{
	auto i = spriteList.find(counter)->second;
	return i;
}

