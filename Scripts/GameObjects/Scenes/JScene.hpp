#pragma once
#include "AScene.hpp"
#include "../Player.hpp"
#include "../Goal.hpp"
#include "../Poolables/Checker.hpp"
#include "../Poolables/Ladder.hpp"
#include "../UI/Level1Map.hpp"
#include "../UI/Level1UI.hpp"
#include "../UI/PauseScreen.hpp"
#include "../UI/ResultScreen.hpp"
#include "../../Components/LadderHandler.hpp"
#include "../../Components/HammerHandler.hpp""
#include "../../Components/BarrelHandler.hpp"
#include "../../Components/PHandler.hpp"
#include "../../Components/KHandler.hpp"
#include "../../Components/CHandler.hpp"
class JScene : public AScene
{
public:
	JScene();

	void onLoadResources();
	void onLoadObjects();

	void onUnloadResources();
};

