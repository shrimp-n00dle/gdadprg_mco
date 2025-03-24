#include "Entity.hpp"

Entity::Entity() {}

void Entity::setTexture(sf::Texture texture)
{
    mTexture = texture;
    mSprite.setTexture(mTexture);
}

sf::Sprite* Entity::getSprite()
{
    return &mSprite;
}

Entity* Entity::createEntity(sf::Texture* texture, float x, float y)
{
    Entity* entity = new Entity();
    entity->setTexture(*texture);
    entity->getSprite()->setPosition(x,y);

    return entity;
}