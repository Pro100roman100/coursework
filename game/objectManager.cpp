#include "objectManager.h"
#include <algorithm>

void ObjectManager::updateAll(float deltaTime)
{
	std::vector<std::shared_ptr<GameObject>> objectsCopy = objects;

	for (auto& obj : objectsCopy)
	{
		if(obj && obj.get() != nullptr)
			obj->update(deltaTime);
	}
}

void ObjectManager::drawAll(sf::RenderWindow* window)
{
	for ( auto& obj : objects)
	{
		if (obj && obj.get() != nullptr)
			window->draw(*obj);
	}
}

void ObjectManager::removeObject(GameObject* object)
{
	auto it = std::find_if(objects.begin(), objects.end(),
		[object](const std::shared_ptr<GameObject>& obj) { return obj.get() == object; });
	if (it != objects.end())
		objects.erase(it);
}

void ObjectManager::clear()
{
	objects.clear();
}