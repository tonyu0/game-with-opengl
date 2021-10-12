#pragma once
#include "Actor.h"

class TargetActor : public Actor {
public:
	TargetActor(class Game* game);
	EActorType GetType() const override { return EActorType::TTargetActor; }
};
