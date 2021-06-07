#pragma once
#include "Math.h"
#include "SoundEvent.h"
#include <string>
#include <unordered_map>

// Forward declarations to avoid including FMOD header
namespace FMOD {
class System;
namespace Studio {
class Bank;
class EventDescription;
class EventInstance;
class System;
class Bus;
}; // namespace Studio
}; // namespace FMOD

class AudioSystem {
public:
  AudioSystem(class Game *game);
  ~AudioSystem();

  bool Initialize();
  void Shutdown();

  // Load/unload banks
  void LoadBank(const std::string &name);
  void UnloadBank(const std::string &name);
  void UnloadAllBanks();

  SoundEvent PlayEvent(const std::string &name); // Specify event name and play.

  void Update(float deltaTime);

  // For positional audio
  void SetListener(const Matrix4 &viewMatrix);
  // Control buses
  float GetBusVolume(const std::string &name) const;
  bool GetBusPaused(const std::string &name) const;
  void SetBusVolume(const std::string &name, float volume);
  void SetBusPaused(const std::string &name, bool pause);

protected:
  // EventInstance pointer dont want to be accessed by external components, but
  // it want to be accessed by SoundEvent.
  friend class SoundEvent;
  FMOD::Studio::EventInstance *GetEventInstance(unsigned int id);

private:
  // Tracks the next ID to use for event instances
  // manage event instance, called 4.3*10^9 times, id will be duplicated.
  static unsigned int sNextID;

  class Game *mGame;
  // Map of loaded banks
  // mBanks["Bank file name"] = Bank
  std::unordered_map<std::string, FMOD::Studio::Bank *> mBanks;
  // Map of event name to EventDescription
  // mEvents["FMOD assigned event name"] = EventDescription
  std::unordered_map<std::string, FMOD::Studio::EventDescription *> mEvents;
  // Map of event id to EventInstance for flexible event operations by
  // SoundEvent class.
  std::unordered_map<unsigned int, FMOD::Studio::EventInstance *>
      mEventInstances;
  // Map of buses, categorized by sound of DSP
  // for instance there are buses of master, SFX, music.
  std::unordered_map<std::string, FMOD::Studio::Bus *> mBuses;
  // FMOD studio system
  FMOD::Studio::System *mSystem;
  // FMOD Low-level system (in case needed)
  FMOD::System *mLowLevelSystem;
};