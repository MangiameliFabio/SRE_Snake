#include "StepMoverComponent.h"
#include "GameObject.h"

StepMoverComponent::StepMoverComponent(GameObject* gameObject) : Component(gameObject) {}

void StepMoverComponent::update(float deltaTime)
{
	if (mCurrentStepDuration >= mSpeed) {
		mCurrentStepDuration = 0.f;
		auto go = getGameObject();
		if (bufferedVelocity + go->getVelocity() != glm::vec2(0,0)) {
			go->setVelocity(bufferedVelocity);
		}
		glm::vec2 newPos = go->getPosition() + go->getVelocity() * 25.f;

		go->setPosition(newPos);
		stepCallback();
	}
	else {
		mCurrentStepDuration += deltaTime;
	}
}

void StepMoverComponent::resetSpeed()
{
	mSpeed = 0.5f;
}

void StepMoverComponent::increaseSpeed()
{
	if (mSpeed > 0.1) {
		mSpeed -= 0.025f;
	}
}
