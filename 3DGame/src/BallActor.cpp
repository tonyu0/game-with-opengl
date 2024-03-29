#include "BallActor.h"
#include "AudioComponent.h"
#include "BallMove.h"
#include "Game.h"
#include "LevelLoader.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"

BallActor::BallActor(Game* game) : Actor(game), mLifeSpan(2.0f) {
	// SetScale(10.0f);
	MeshComponent* mc = new MeshComponent(this);
	Mesh* mesh = GetGame()->GetRenderer()->GetMesh("Assets/Sphere.gpmesh");
	mc->SetMesh(mesh);
	BallMove* move = new BallMove(this);
	move->SetForwardSpeed(1500.0f);
	mAudioComp = new AudioComponent(this);
}

void BallActor::UpdateActor(float deltaTime) {
	Actor::UpdateActor(deltaTime);

	mLifeSpan -= deltaTime;
	if (mLifeSpan < 0.0f) {
		SetState(EState::EDead);
	}
}

void BallActor::HitTarget() { mAudioComp->PlayEvent("event:/Ding"); }

void BallActor::LoadProperties(const rapidjson::Value& inObj) {
	Actor::LoadProperties(inObj);
	JsonHelper::GetFloat(inObj, "lifespan", mLifeSpan);
}

void BallActor::SaveProperties(rapidjson::Document::AllocatorType& alloc,
	rapidjson::Value& inObj) const {
	Actor::SaveProperties(alloc, inObj);
	JsonHelper::AddFloat(alloc, inObj, "lifespan", mLifeSpan);
}
