#pragma once
#include "AScene.hpp"
#include "../Player.hpp"
#include "../Poolables/Ladder.hpp"
#include "../UI/Level1Map.hpp"
#include "../../Components/LadderHandler.hpp"
#include "../../Components/HammerHandler.hpp"
class JScene : public AScene
{
public:
	JScene();

	void onLoadResources();
	void onLoadObjects();

	void onUnloadResources();
};

