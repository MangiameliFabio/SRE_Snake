#pragma once

#include "Component.h"
#include "sre/Sprite.hpp"

class StepMoverComponent : public Component {
public:
    explicit StepMoverComponent(GameObject* gameObject);

    void update(float deltaTime) override;

    void increaseSpeed();

    void resetSpeed();

    std::function<void()> stepCallback;
    glm::vec2 bufferedVelocity = { 0,0 };
private:
    float mSpeed = 0.5f;
    float mCurrentStepDuration = 0.f;
};

