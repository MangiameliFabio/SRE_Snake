#pragma once
#include "Component.h"

class SnakeHeadComponent : public Component {
public:
    explicit SnakeHeadComponent(GameObject* gameObject);

    void init();

    bool onKey(SDL_Event& event) override;

    void update(float deltaTime) override;

    void onMoveStep();

    void moveBody();

    void checkForFruit();

    void checkForCollision();

    void addBodyPart();

    void setTargetFruit(GameObject* gameObject);

private:
    GameObject* mTargetFruit = nullptr;
    std::vector<std::shared_ptr<GameObject>> body;
    glm::vec2 lastLocation = { 0,0 };
};