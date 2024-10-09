#include "Globals.h"
#include "GameObject.h"
#include <vector>
#include <memory>

std::vector<std::shared_ptr<GameObject>> Globals::sceneObjects;
std::shared_ptr<sre::SpriteAtlas> Globals::atlas;
glm::vec2 Globals::window_size;

std::shared_ptr<GameObject> Globals::createGameObject(){
	auto obj = std::make_shared<GameObject>();
	sceneObjects.push_back(obj);

	return obj;
}