#pragma once
#include "Actor.h"

class PlaneActor : public Actor {
public:
	PlaneActor(class Game* game);
	EActorType GetType() const override { return EActorType::TPlaneActor; }
};
