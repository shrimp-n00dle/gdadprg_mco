#pragma once
#include "../GameObjects/Scenes/AScene.hpp"
#include "unordered_map"

typedef std::unordered_map<std::string, AScene*> SceneTable;
typedef std::vector<std::string> SceneList;

class SceneManager
{
public:
	//scene names
	static std::string MAIN_MENU_SCENE_NAME;
	static std::string GAME_SCENE_NAME;
	static std::string SPRITE_SCENE_NAME;
	static std::string MCOGAME_SCENE_NAME;

	static SceneManager* getInstance();
	void registerScene(AScene* scene);
	void loadScene(std::string name); //also calls unload of the previous scene automatically
	void unloadScene();
	bool isSceneLoaded(std::string name);
	void checkLoadScene();

	AScene* getActiveScene();

private:
	SceneManager() {};
	SceneManager(SceneManager const&) {}; //copy constructor is private
	SceneManager& operator=(SceneManager const&) {}; //assignment operator is private
	static SceneManager* sharedInstance;

	SceneTable storedScenes;
	//SceneTable activeScene;
	AScene* activeScene;
	std::string toLoadSceneName;
	bool isLoading = false;
};

