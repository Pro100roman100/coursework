#pragma once

#include "gameObject.h"
#include "resourceManager.h"
#include "consts.h"

class Tile : public GameObject
{
public:
    Tile(const sf::Texture& texture) : GameObject(texture) { }

    void update(float deltaTime) override {}

    Collider getCollider() const override {
        return BoxCollider(getPosition(), sf::Vector2f(tileSize, tileSize));
    }

    PhysicsObject::ObjectType getType() const override {
        return PhysicsObject::ObjectType::_static_;
    }
};

class TileFactory : public ObjectFactory {
public:
    static std::shared_ptr<GameObject> createObject() {
        return std::make_shared<Tile>(ResourceManager::getInstance().getTexture(ResourceManager::Texture::tile));
    }
};