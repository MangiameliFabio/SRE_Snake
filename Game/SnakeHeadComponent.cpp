#include "SnakeHeadComponent.h"

#include "GameObject.h"
#include "FruitComponent.h"
#include "SpriteComponent.h"
#include "Globals.h"

#include "SDL_events.h"
#include "sre/SpriteAtlas.hpp"
#include <memory>
#include <StepMoverComponent.h>

SnakeHeadComponent::SnakeHeadComponent(GameObject* gameObject) : Component(gameObject){}

void SnakeHeadComponent::init()
{
    lastLocation = getGameObject()->getPosition();
}

bool SnakeHeadComponent::onKey(SDL_Event& event)
{
    switch (event.key.keysym.sym) {
        case SDLK_w:
            getGameObject()->getComponent<StepMoverComponent>()->bufferedVelocity = {0, 1};
            return true;
        case SDLK_a:
            getGameObject()->getComponent<StepMoverComponent>()->bufferedVelocity = { -1, 0 };
            return true;
        case SDLK_s:
            getGameObject()->getComponent<StepMoverComponent>()->bufferedVelocity = { 0, -1 };
            return true;
        case SDLK_d:
            getGameObject()->getComponent<StepMoverComponent>()->bufferedVelocity = { 1, 0 };
            return true;
        default:
            break;
    }

	return false;
}

void SnakeHeadComponent::update(float deltaTime)
{
}

void SnakeHeadComponent::onMoveStep()
{
    moveBody();
    checkForCollision();
    checkForFruit();
    lastLocation = getGameObject()->getPosition();
}

void SnakeHeadComponent::moveBody() {
    glm::vec2 tail_pos = lastLocation;

    for (size_t i = 0; i < body.size(); i++) {
        glm::vec2 temp = body[i]->getPosition();
        body[i]->setPosition(lastLocation);
        lastLocation = temp;
    }
}

void SnakeHeadComponent::checkForFruit()
{
    if (mTargetFruit == nullptr) { return; }

    if (getGameObject()->getPosition() == mTargetFruit->getPosition()) {
        auto fc = mTargetFruit->getComponent<FruitComponent>();
        if (fc) {
            bool fruitSpawned = false;
            while (!fruitSpawned) {
                fc->setFruitPosRand(Globals::window_size);
                fruitSpawned = true;
                for (auto part : body) {
                    if (part->getPosition() == fc->getGameObject()->getPosition()) {
                        fruitSpawned = false;
                    }
                }
            }
            addBodyPart();
            getGameObject()->getComponent<StepMoverComponent>()->increaseSpeed();
        }
    }
}

void SnakeHeadComponent::checkForCollision()
{
    bool collision = false;
    for (auto part : body) {
        if (getGameObject()->getPosition() == part->getPosition()) {
            collision = true;
        }
    }
    if (getGameObject()->getPosition().x <= 0.f || 
        getGameObject()->getPosition().x >= Globals::window_size.x ||
        getGameObject()->getPosition().y <= 0.f ||
        getGameObject()->getPosition().y >= Globals::window_size.y) 
    {
        collision = true;
    }

    if (collision) {
        for (size_t i = 0; i < body.size(); i++) {
            body[i]->cleanGameObject();
        }
        body.clear();
        getGameObject()->setPosition(Globals::window_size / 2.f);
        getGameObject()->setVelocity({ 0,0 });
        auto sm = getGameObject()->getComponent<StepMoverComponent>();
        sm->resetSpeed();
        sm->bufferedVelocity = glm::vec2{ 0,0 };
    }
}

void SnakeHeadComponent::addBodyPart()
{
    auto part = Globals::createGameObject();
    part->name = "BodyPart";
    auto sprite = part->addComponent<SpriteComponent>();
    sprite->setSprite(Globals::atlas->get("snake-body.png"));
    part->setPosition(lastLocation);

    body.push_back(part);
}

void SnakeHeadComponent::setTargetFruit(GameObject* gameObject)
{
    SnakeHeadComponent::mTargetFruit = gameObject;
}
