#include "physicsObject.h"
#include "physicsManager.h"

PhysicsObject::PhysicsObject() {
    PhysicsManager::getInstance().addPhysicsObject(this);
}

PhysicsObject::~PhysicsObject() {
    PhysicsManager::getInstance().removePhysicsObject(this);
}