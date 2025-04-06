#pragma once
#include "../AGameObject.hpp"
#include "../../Managers/GameObjectManager.hpp"

//deals with the loading and unloading of objects, then registering them to object manager
//also does the opposite, unloading
class AScene
{
public:
	AScene(std::string sceneName);

	virtual void onLoadResources() = 0;
	virtual void onLoadObjects() = 0;

	virtual void onUnloadResources() = 0;
	virtual void onUnloadObjects();

	std::string getSceneName();

	//IMPORTANT: this must be  called for every object to be loaded/unloaded
	void registerObject(AGameObject* object);
protected:
	
	std::string sceneName;
};

