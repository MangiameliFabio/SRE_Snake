#pragma once

#include "Globals.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "StepMoverComponent.h"
#include "SnakeHeadComponent.h"
#include "FruitComponent.h"

#include <memory>
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

sre::SDLRenderer renderer;
sre::Camera camera;

void ProcessEvents(SDL_Event& event) {
	for (auto& gameObject : Globals::sceneObjects) {
		for (auto& c : gameObject->getComponents()) {
			bool consumed = c->onKey(event);
			if (consumed) {
				return;
			}
		}
	}
}
void Update(float deltaTime) {
	bool cleanUp = false;
	for (int i = 0; i < Globals::sceneObjects.size(); i++) {
		if (Globals::sceneObjects[i]->markedForDeletion) {
			Globals::sceneObjects[i] = nullptr;
			cleanUp = true;
			continue;
		}
		Globals::sceneObjects[i]->update(deltaTime);
	}
	if (cleanUp) {
		Globals::sceneObjects.erase(
			std::remove(begin(Globals::sceneObjects),
				end(Globals::sceneObjects), nullptr),
			end(Globals::sceneObjects));
	}
}
void Render() {
	sre::RenderPass renderPass = sre::RenderPass::create()
		.withCamera(camera)
		.withClearColor(true, { .3f, .3f, 1, 1 })
		.build();
	sre::SpriteBatch::SpriteBatchBuilder spriteBatchBuilder
		= sre::SpriteBatch::create();
	// send spriteBatchBuilder to your game elements, so that
	//they can add their sprites for rendering
	for (int i = 0; i < Globals::sceneObjects.size(); i++) {
		Globals::sceneObjects[i]->renderSprite(spriteBatchBuilder);
	}
	auto spriteBatch = spriteBatchBuilder.build();
	renderPass.draw(spriteBatch);
}

int main() {
	Globals::window_size = glm::vec2(800, 600);

	renderer.frameRender = Render;
	renderer.frameUpdate = Update;
	renderer.keyEvent = ProcessEvents;
	renderer.setWindowSize(Globals::window_size);
	renderer.init();
	camera.setWindowCoordinates();

	Globals::atlas = sre::SpriteAtlas::create("data/snake.json",
		"data/snake.png");
	
	auto snake = Globals::createGameObject();
	snake->name = "Snake";
	snake->setPosition(Globals::window_size / 2.f);
	
	auto snakeSprite = snake->addComponent<SpriteComponent>();
	snakeSprite->setSprite(Globals::atlas->get("snake-body.png"));
	auto snakeHead = snake->addComponent<SnakeHeadComponent>();
	snakeHead->init();
	auto mover = snake->addComponent<StepMoverComponent>();
	mover->stepCallback = [&snakeHead]() { snakeHead->onMoveStep(); };

	auto fruit = Globals::createGameObject();
	fruit->name = "Fruit";
	auto fruitSprite = fruit->addComponent<SpriteComponent>();
	fruitSprite->setSprite(Globals::atlas->get("berry.png"));
	auto fruitComponent = fruit->addComponent<FruitComponent>();
	fruitComponent->setFruitPosRand(Globals::window_size);
	snakeHead->setTargetFruit(fruit.get());

	renderer.startEventLoop();
}
