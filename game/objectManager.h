#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "gameObject.h"
#include "singleton.h"

class ObjectManager : public Singleton<ObjectManager>
{
    friend class Singleton<ObjectManager>;

private:

    ObjectManager() = default;

    std::vector<std::shared_ptr<GameObject>> objects;

public:
    template<std::derived_from<ObjectFactory> T>
    std::shared_ptr<GameObject> addObject()
    {
        auto obj = T::createObject();
        objects.push_back(obj);
        return obj;
    }

    void removeObject(GameObject* object);

    const std::vector<std::shared_ptr<GameObject>>& getObjects() const
    {
        return objects;
    }

    void updateAll(float deltaTime);
    void drawAll(sf::RenderWindow* window);
    void clear();
};