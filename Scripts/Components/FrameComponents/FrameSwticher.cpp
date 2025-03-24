#include "FrameSwticher.hpp"

FrameSwitcher::FrameSwitcher(std::string name) : AComponent(name, Script) 
{
	initializeSprites();
}

void FrameSwitcher::perform()
{
	SpriteFrame* frameObj = (SpriteFrame*)this->getOwner();
	FrameInput* frameInputController = (FrameInput*)(frameObj->getComponentsOfType(ComponentType::Input)[0]);
	sf::Transformable* frameTransformable = frameObj->getTransformable();

	/*Checkers*/
	if (frameTransformable == nullptr ) std::cout << "frameTransformable not found" << std::endl;
	if (frameInputController == nullptr)  std::cout << "frameInputController not found" << std::endl;


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

	/*if its a negative number, or is beyond 38 go to the beginning of the list and set coutner to 0 or 38*/
	if (counter > 38) counter = 0;
	else if (counter < 0) counter = 38;

	coord = traverseList(counter);

	/*Sprite Rendering*/
	currSprite = sf::IntRect(coord[0], coord[1], coord[2], coord[3]);
	frameObj->frameSprite->setTextureRect(currSprite);
	frameObj->frameSprite->setOrigin(currSprite.width / 2, currSprite.height / 2);
}

void FrameSwitcher::initializeSprites()
{
	//1. Parse a JSON file
	FILE* file = fopen("Assets/SpriteSheets/Dota_Sheet.json", "rb");

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

	//{"x":0, "y" : 0, "w" : 150, "h" : 84},
	coord = { 0,0,150,84 };
	//currSprite = sf::IntRect(0, 0, 150, 84);
}

std::vector<int> FrameSwitcher::traverseList(int counter)
{
	auto i = spriteList.find(counter)->second;
	return i;
}

