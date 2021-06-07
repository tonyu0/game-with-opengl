#include "CameraComponent.h"
#include "Actor.h"
#include "AudioSystem.h"
#include "Game.h"
#include "Renderer.h"

CameraComponent::CameraComponent(Actor *owner, int updateOrder)
    : Component(owner, updateOrder) {}

void CameraComponent::SetViewMatrix(const Matrix4 &view) {
  // Pass view matrix to renderer and audio system
  Game *game = mOwner->GetGame();
  game->GetRenderer()->SetViewMatrix(view);
  game->GetAudioSystem()->SetListener(view);
}
