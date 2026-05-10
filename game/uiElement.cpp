#include "uiElement.h"


void UiElement::setUpdate(std::function<void(float)> function)
{
	updateFunc = function;
}

void UiElement::setOnClick(std::function<void()> function)
{
	onClickFunc = function;
}

void UiElement::update(float deltaTime)
{
	updateFunc(deltaTime);
}

void UiElement::onClick()
{
	onClickFunc();
}
