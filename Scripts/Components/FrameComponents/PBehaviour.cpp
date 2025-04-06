#include "PBehaviour.hpp"

PBehaviour::PBehaviour(std::string name) : AComponent(name, Script)
{
	initializeSprites();
}

void PBehaviour::perform()
{
	Princess* frameObj = (Princess*)this->getOwner();

		/*If timer is less than 0 seconds*/
		if (frameObj->timer <= 0.0f)
		{
			counter++;
			/*if its a negative number, or is beyond, go to the beginning of the list and set coutner to 0 or the maximum*/
			if (counter >= 2) counter = 0;
			frameObj->timer = 2.0f;
		}

		coord = traverseList(counter);

		/*Sprite Rendering*/
		currSprite = sf::IntRect(coord[0], coord[1], coord[2], coord[3]);
		frameObj->frameSprite->setTextureRect(currSprite);
		frameObj->frameSprite->setOrigin(currSprite.width / 2.0f, currSprite.height / 2.0f);
	}

void PBehaviour::initializeSprites()
{
	//1. Parse a JSON file
	FILE* file = fopen("Assets/MCOAssets/SpriteSheet/Princess/Princess.json", "rb");

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

	//"frame": {"x":0,"y":0,"w":16,"h":24},
	coord = { 0,0,16,24};
}

std::vector<int> PBehaviour::traverseList(int counter)
{
	auto i = spriteList.find(counter)->second;
	return i;
}

