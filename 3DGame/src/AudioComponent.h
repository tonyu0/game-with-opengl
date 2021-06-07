#pragma once
#include "Component.h"
#include "SoundEvent.h"
#include <string>
#include <vector>

// Attach SoundEvent to Actor.
// When Actor moving, it can update 3D attr of SoundEvent.
class AudioComponent : public Component {
public:
  AudioComponent(class Actor *owner, int updateOrder = 200);
  ~AudioComponent();

  void Update(float deltaTime) override;
  void OnUpdateWorldTransform() override;

  SoundEvent PlayEvent(const std::string &name);
  void StopAllEvents();

  TypeID GetType() const override { return TAudioComponent; }

private:
  std::vector<SoundEvent> mEvents2D;
  std::vector<SoundEvent> mEvents3D;
};