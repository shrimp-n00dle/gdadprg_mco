#pragma once
#include "string"
#include "iostream"
#include "SFML/Graphics.hpp"
#include "../Components/AComponent.hpp"
#include "../Inputs/GenericInput.hpp"
#include "../Renderer/Renderer.hpp"


 class AGameObject
 {
 public:
     AGameObject(std::string name);
     virtual ~AGameObject();
     virtual void initialize();
     virtual void processInput(sf::Event event);
     virtual void update(sf::Time deltaTime);
     virtual void draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);
     std::string getName();

     void attachComponent(AComponent* component);
     void detachComponent(AComponent* component);
     AComponent* findComponentByName(std::string name);
     AComponent* findComponentByType(AComponent::ComponentType type, std::string name);
     std::vector<AComponent*> getComponentsOfType(AComponent::ComponentType type);
     //std::vector<AComponent*> getComponentsOfTypeRecursive(AComponent::ComponentType type);

     void attachChild(AGameObject* child);
     void detachChild(AGameObject* child);
     void setChildPosition(float x, float y);
     sf::Transformable* getTransformable();
     sf::Transform getGlobalTransform();

     void setEnabled(bool flag);
     bool isEnabled();

     AGameObject* getParent();

 protected:
     void setParent(AGameObject* gameObject);
     sf::Transformable transformable;
     std::string name;
     sf::Sprite* sprite;
     sf::Texture* texture;
     std::vector<AGameObject*> childList;
     std::vector<AComponent*> componentList;

 private:
     Renderer* renderer;
     AGameObject* mParent;
     //std::vector<AComponent*> getComponentsRecursiveProper(AGameObject* object, AComponent::ComponentType type, std::vector<AComponent*> foundList);
     bool enabled = true;
 };