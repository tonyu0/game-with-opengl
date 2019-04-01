//
//  AudioSystem.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/04/01.
//  Copyright © 2019 Nakagawa. All rights reserved.
//
#pragma once
#ifndef AudioSystem_hpp
#define AudioSystem_hpp
#include <string>
#include <unordered_map>
#include <fmod_studio.hpp>
#include <vector>
#include "SoundEvent.hpp"

#endif /* AudioSystem_hpp */

// AudioSystem : 音を鳴らす専用のクラス

class AudioSystem{
public:
    AudioSystem(class Game* game);
    ~AudioSystem();
    bool Initialize();
    void Update(float deltaTime);
    void ShutDown();
    
    void LoadBank(const std::string& name);
    void UnloadBank(const std::string& name);
    
    // Play
    SoundEvent PlayEvent(const std::string& name); // イベントを指定して再生
    
    // Setter
    void SetListener(const Matrix4& view);
    
    // Bus Setting
    float GetBusVolume(const std::string& name) const;
    bool GetBusPaused(const std::string& name) const;
    void SetBusVolume(const std::string& name, float volume);
    void SetBusPaused(const std::string& name, bool pause);
protected:
    // EventInstanceポインタは外部からアクセスされたくないが、SoundEventからはアクセスしたい。
    friend class SoundEvent; // 親子関係がなくてもSoundEventのみアクセス可能
    FMOD::Studio::EventInstance* GetEventInstance(unsigned int id); // idで指定たイベントがあれば返す。
private:
    // いベントインスタンス管理用 43億回ほど呼び出すとIDが重複する。
    static unsigned int sID;
    
    class Game* mGame;
    FMOD::Studio::System* mSystem;
    FMOD::System* mLowLevelSystem;
    
    // ロードされたバンク map[バンクのファイル名] = Bank
    std::unordered_map<std::string, FMOD::Studio::Bank*> mBanks;
    // イベント名からEventDescriptionへの連想配列 map[FMODが割り当てたイベント名] = EventDescription
    std::unordered_map<std::string, FMOD::Studio::EventDescription*> mEvents;
    // イベントインスタンスをIDで管理(SoundEventクラスによる柔軟なイベント操作のため)
    std::unordered_map<unsigned int, FMOD::Studio::EventInstance*> mEventInstances;
    // バス。DSPをかけたいサウンドごとにカテゴリ分け
    // 例えばmaster, SFX, musicなどのバスがある。
    std::unordered_map<std::string, FMOD::Studio::Bus*> mBuses;
    // スナップショット　：　バスを制御する特殊なイベント
};
