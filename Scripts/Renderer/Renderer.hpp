#pragma once
#include "../Components/AComponent.hpp"
#include "SFML/Graphics.hpp"

class Renderer : public AComponent
{
public:
	Renderer(std::string name);
	~Renderer();

	void assignTargetWindow(sf::RenderWindow* window);
	void assignDrawable(sf::Drawable* drawable);
	void setRenderStates(sf::RenderStates renderStates);

	void perform();

private:
	sf::RenderWindow* targetWindow;
	sf::Drawable* drawable;
	sf::RenderStates renderStates;
};

