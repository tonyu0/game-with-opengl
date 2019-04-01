//
//  SoundEvent.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/04/01.
//  Copyright © 2019 Nakagawa. All rights reserved.
//
#pragma once
#ifndef SoundEvent_hpp
#define SoundEvent_hpp

#include "Math.hpp"
#include <string>

#endif /* SoundEvent_hpp */

// SoundEventはじ実体が必要なのでポインタでは扱わない？
class SoundEvent {
public:
    SoundEvent();
    // 対応するFMODインスタンスが存在したらtrueを返す。
    bool IsValid();
    // イベントをリスタート
    void Restart();
    // イベントをストップ
    void Stop(bool allowFadeOut=true);
    
    // Setters
    void SetPaused(bool pause);
    void SetVolume(float value);
    void SetPitch(float value);
    void SetParameter(const std::string& name, float value);
    // Getters
    bool GetPaused() const;
    float GetVolume() const;
    float GetPitch() const;
    float GetParameter(const std::string& name);
    // Positional
    bool Is3D() const;
    void Set3DAttributes(const Matrix4& worldTrans);
protected:
    // フレンドにしてprotectedにすることでAudioSystemのみから
    friend class AudioSystem;
    SoundEvent(class AudioSystem* sys, unsigned int id);
private:
    class AudioSystem* mSystem;
    unsigned int mID;
};
