#pragma once
#include <glm/glm.hpp>
#include "GameObject.h"

class GameObject;

class Globals {
public: 
	static glm::vec2 window_size;
	static std::vector<std::shared_ptr<GameObject>> sceneObjects;
	static std::shared_ptr<sre::SpriteAtlas> atlas;

	static std::shared_ptr<GameObject> createGameObject();
};