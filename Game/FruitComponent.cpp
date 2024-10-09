#include "FruitComponent.h"
#include "Engine/GameObject.h"
#include <random>

FruitComponent::FruitComponent(GameObject* gameObject) : Component(gameObject) {}

void FruitComponent::setFruitPosRand(glm::vec2 &area)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution_x(25, area.x - 25);
    std::uniform_int_distribution<> distribution_y(25, area.y - 25);

    int randX = distribution_x(generator);
    int randY = distribution_y(generator);

    int multiX = static_cast<float>(randX) / 25.f;
    int multiY = static_cast<float>(randY) / 25.f;

	getGameObject()->setPosition({ 25 * multiX, 25 * multiY });
}
