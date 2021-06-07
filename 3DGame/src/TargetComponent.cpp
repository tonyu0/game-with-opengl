#include "TargetComponent.h"
#include "Actor.h"
#include "BoxComponent.h"
#include "Game.h"
#include "HUD.h"
#include "Math.h"
#include "PhysWorld.h"


TargetComponent::TargetComponent(Actor *owner) : Component(owner) {
  mOwner->GetGame()->GetHUD()->AddTargetComponent(this);
}

TargetComponent::~TargetComponent() {
  mOwner->GetGame()->GetHUD()->RemoveTargetComponent(this);
}
