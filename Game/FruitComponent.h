#pragma once
#include "Component.h"

class FruitComponent : public Component {
public:
    explicit FruitComponent(GameObject* gameObject);

    void setFruitPosRand(glm::vec2 &area);
};