#include "camera.h"

Camera* Camera::activeCamera = nullptr;

Camera::Camera() {
    setScale(windowSize);
    view.zoom(1.0f / pixelRatio);
}

Camera* Camera::getActive() {
    return activeCamera;
}

void Camera::setActive() {
    activeCamera = this;
}

void Camera::setTarget(std::shared_ptr<GameObject> newTarget) {
    target = newTarget;
    auto targetPtr = target.lock();
    if (targetPtr.get() != nullptr)
        setCenter(targetPtr->getPosition());
}

void Camera::update(float deltaTime) {
    auto targetPtr = target.lock();
    if (targetPtr.get() != nullptr) {
        sf::Vector2f currentCenter = view.getCenter();
        sf::Vector2f targetCenter = targetPtr->getPosition();

        float lerpSpeed = 5.0f;
        sf::Vector2f newCenter = currentCenter + (targetCenter - currentCenter) * (lerpSpeed * deltaTime);

        setCenter(newCenter);
    }
}

sf::View& Camera::getView() {
    return view;
}

void Camera::setScale(const sf::Vector2f& size) {
    view.setSize(size);
}

void Camera::setCenter(const sf::Vector2f& center) {
    view.setCenter(center);
}
