#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "gameObject.h"
#include "consts.h"

class Camera
{
private:
    sf::View view;
    std::weak_ptr<GameObject> target;

    static Camera* activeCamera;

public:
    Camera();

    static Camera* getActive();
    void setActive();

    void setTarget(std::shared_ptr<GameObject> newTarget);

    void update(float deltaTime);

    sf::View& getView();
    void setScale(const sf::Vector2f& size);
    void setCenter(const sf::Vector2f& center);
};
