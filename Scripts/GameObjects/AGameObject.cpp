 #include "AGameObject.hpp"

 AGameObject::AGameObject(std::string name)
 {
     this->name = name;
 }

 AGameObject::~AGameObject()
 {
     if (this->sprite != nullptr)
     {
         delete this->sprite;
     }

     for (int i = 0; i < this->componentList.size(); i++)
     {
         delete this->componentList[i];
     }

     for (int i = 0; i < this->childList.size(); i++)
     {
         delete this->childList[i];
     }
 }

 std::string AGameObject::getName()
 {
     return name;
 }

 void AGameObject::initialize() {}

void AGameObject::processInput(sf::Event event) 
{
   
    if (!isEnabled()) return;

    //process input here
    std::vector<AComponent*> componentList = this->getComponentsOfType(AComponent::ComponentType::Input);

    for (int j = 0; j < componentList.size(); j++)
    {
        ((GenericInput*)componentList[j])->assignEvent(event);
        componentList[j]->perform();
    }

    for (int i = 0; i < this->childList.size(); i++)
    {
        childList[i]->processInput(event);
    }

}

 void AGameObject::update(sf::Time deltaTime)
 {
     if (!isEnabled()) return;

     //std::cout << "update";

     std::vector<AComponent*> componentList = this->getComponentsOfType(AComponent::ComponentType::Script);

     for (int j = 0; j < componentList.size(); j++)
     {
         componentList[j]->setDeltaTime(deltaTime);
         componentList[j]->perform();
     }

     for (int i = 0; i < childList.size(); i++)
     {
         childList[i]->update(deltaTime);
     }

     /*
     for (int i = 0; i < this->childList.size(); i++)
     {

         if (childList[i]->
         ) childList[i]->transformable.move(-1.0f, 0.0f);
         else childList[i]->transformable.move(1.0f, 0.0f);

         //If the ship is on the right
         if (childList[i]->transformable.getPosition().x <= -50) childList[i]->bReturn = false;
         //If the ship is on the left
         else if (childList[i]->transformable.getPosition().x >= 50) childList[i]->bReturn = true;

     }
    */
     


 }

 void AGameObject::draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
 {  
     if (!isEnabled()) return;

     renderStates.transform = renderStates.transform * this->transformable.getTransform();
     
     //targetWindow->draw(*sprite, renderStates);

     std::vector<AComponent*> componentList = getComponentsOfType(AComponent::ComponentType::Renderer);

     for (int j = 0; j < componentList.size(); j++)
     {
         Renderer* renderer = (Renderer*)componentList[j];
         renderer->assignTargetWindow(targetWindow);
         renderer->setRenderStates(renderStates);
         renderer->perform();
     }

     for (int i = 0; i < this->childList.size(); i++)
     {
         AGameObject* child = this->childList[i];
         child->draw(targetWindow, renderStates);
     }
 }

 void AGameObject::attachChild(AGameObject* child)
 {
     this->childList.push_back(child);
     child->setParent(this);
     child->initialize();
 }

 void AGameObject::detachChild(AGameObject* child)
 {
     int index = -1;
     for (int i = 0; i < this->childList.size(); i++)
     {
         if (this->childList[i] == child)
         {
             index = i;
         }
     }

     if (index != -1)
     {
         this->childList.erase(this->childList.begin() + index);
         this->childList.shrink_to_fit();
     }
 }

 void AGameObject::setChildPosition(float x, float y)
 {
     this->transformable.setPosition(x, y);
 }

 sf::Transformable* AGameObject::getTransformable()
 {
     return &transformable;
 }

 void AGameObject::attachComponent(AComponent* component)
 {
     this->componentList.push_back(component);
     component->attachOwner(this);
 }

 void AGameObject::detachComponent(AComponent* component)
 {
     int index = -1;
     for (int i = 0; i < this->componentList.size(); i++)
     {
         if (this->componentList[i] == component)
         {
             index = i;
             /*Detach it from owner*/
             this->componentList[i]->detachOwner();
             break;
         }
   
     }

     /*Remove it from the list*/
     if (index != -1) this->componentList.erase(componentList.begin() + index);
 }

 AComponent* AGameObject::findComponentByName(std::string name)
 {
     for (int i = 0; i < this->componentList.size(); i++)
     {
         if (this->componentList[i]->getName() == name)
             return this->componentList[i];
     }

     return NULL;
 }

 AComponent* AGameObject::findComponentByType(AComponent::ComponentType type, std::string name)
 {
     for (int i = 0; i < this->componentList.size(); i++)
     {
         if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type)
             return this->componentList[i];
     }

     return NULL;
 }

 std::vector<AComponent*> AGameObject::getComponentsOfType(AComponent::ComponentType type)
 {
     std::vector<AComponent*> foundList;


     for (int i = 0; i < this->componentList.size(); i++)
     {
         if (this->componentList[i]->getType() == type) foundList.push_back(this->componentList[i]);
         
     }   

     return foundList;

 }

 void AGameObject::setEnabled(bool flag) 
 {
     enabled = flag;
 }

 bool AGameObject::isEnabled()
 {
     return enabled;
 }



 AGameObject* AGameObject::getParent()
 {
     return this->mParent;
 }

 void AGameObject::setParent(AGameObject* parent)
 {
     this->mParent = parent;
 }

 sf::Transform AGameObject::getGlobalTransform()
 {
     AGameObject* parentObj = this;
     std::vector<AGameObject*> parentList;

     while (parentObj != NULL)
     {
         parentList.push_back(parentObj);
         parentObj = parentObj->getParent();

     }

     sf::Transform transform = sf::Transform::Identity;
     int startIdx = parentList.size() - 1;
     for (int i = startIdx; i >= 0; i--)
     {
         transform = transform * parentList[i]->getTransformable()->getTransform();
     }

     return transform;
 }
 /*std::vector<AComponent*> AGameObject::getComponentsOfTypeRecursive(AComponent::ComponentType type)
 {
     std::vector<AComponent*> foundList;

     for (int i = 0; i < componentList.size(); i++)
     {
         if (componentList[i]->getType() == type)
         {
             foundList.push_back(componentList[i]);
         }
     }

     for (int i = 0; i < childList.size(); i++)
     {
         foundList = getComponentsRecursiveProper(childList[i], type, foundList);
     }

     return foundList;
 }

 std::vector<AComponent*> AGameObject::getComponentsRecursiveProper(AGameObject* object, AComponent::ComponentType type, std::vector<AComponent*> foundList)
 {
     return foundList;

 }*/