#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <variant>
#include <memory>

class BoxCollider {
	sf::Vector2f center;
	sf::Vector2f size;
public:
	BoxCollider(sf::Vector2f center, sf::Vector2f size) : center(center), size(size) {}
	sf::Vector2f getCenter() const { return center; }
	sf::Vector2f getSize() const { return size; }
};

class CircleCollider {
	sf::Vector2f center;
	float radius;
public:
	CircleCollider(sf::Vector2f center, float radius) : center(center), radius(radius) {}
	sf::Vector2f getCenter() const { return center; }
	float getRadius() const { return radius; }
};

using Collider = std::variant<BoxCollider, CircleCollider>;

class PhysicsObject {
public:

	enum class ObjectType {
		_dynamic_,
		_static_,
		_trigger_
	};

protected:

	PhysicsObject();
	virtual ~PhysicsObject();

	PhysicsObject(const PhysicsObject&) = delete;
	PhysicsObject(PhysicsObject&&) = delete;
	PhysicsObject& operator=(const PhysicsObject&) = delete;
	PhysicsObject& operator=(PhysicsObject&&) = delete;

public:

	virtual Collider getCollider() const = 0;
	virtual ObjectType getType() const = 0;
	virtual void move(sf::Vector2f transform) = 0;
	virtual void onCollision(PhysicsObject* target) = 0;
};