#pragma once
#include "Actor.h"

class BallActor : public Actor {
public:
	BallActor(class Game* game);

	void UpdateActor(float deltaTime) override;

	void HitTarget();

	void LoadProperties(const rapidjson::Value& inObj) override;
	void SaveProperties(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObj) const override;

	EActorType GetType() const override { return EActorType::TBallActor; }

private:
	class AudioComponent* mAudioComp;
	float mLifeSpan;
};
