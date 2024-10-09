#pragma once
#include "Component.h"

class SnakeBodyComponent : public Component {
public:
    explicit SnakeBodyComponent(GameObject* gameObject);

    void updat(glm::vec2& area);
};