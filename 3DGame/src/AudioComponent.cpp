#include "AudioComponent.h"
#include "Actor.h"
#include "AudioSystem.h"
#include "Game.h"

AudioComponent::AudioComponent(Actor* owner, int updateOrder)
	: Component(owner, updateOrder) {}

AudioComponent::~AudioComponent() { StopAllEvents(); }

void AudioComponent::Update(float deltaTime) {
	Component::Update(deltaTime);
	// invalid: SoundEvent without AudioSystem or EventInstance/

	// Remove invalid 2D events
	for (auto itr = mEvents2D.begin(); itr != mEvents2D.end(); ++itr) {
		if (!itr->IsValid()) {
			mEvents2D.erase(itr);
		}
	}
	for (auto itr = mEvents3D.begin(); itr != mEvents3D.end(); ++itr) {
		if (!itr->IsValid()) {
			mEvents3D.erase(itr);
		}
	}
}

void AudioComponent::OnUpdateWorldTransform() {
	// Update 3D events' world transforms
	Matrix4 world = mOwner->GetWorldTransform();
	for (auto& event : mEvents3D) {
		if (event.IsValid()) {
			event.Set3DAttributes(world);
		}
	}
}

SoundEvent AudioComponent::PlayEvent(const std::string& name) {
	// Use event name to fetch SoundEvent instance.
	SoundEvent e = mOwner->GetGame()->GetAudioSystem()->PlayEvent(name);
	// Is this 2D or 3D?
	if (e.Is3D()) {
		mEvents3D.emplace_back(e);
		// Set initial 3D attributes
		e.Set3DAttributes(mOwner->GetWorldTransform());
		// Set 3D attr from Actor's world matrix.
	}
	else {
		mEvents2D.emplace_back(e);
	}
	return e;
}

void AudioComponent::StopAllEvents() {
	// Stop all sounds
	for (auto& e : mEvents2D) {
		e.Stop();
	}
	for (auto& e : mEvents3D) {
		e.Stop();
	}
	// Clear events
	mEvents2D.clear();
	mEvents3D.clear();
}
