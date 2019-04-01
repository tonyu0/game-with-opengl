//
//  SoundEvent.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/04/01.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "SoundEvent.hpp"
#include "AudioSystem.hpp"
#include <fmod_studio.hpp>



SoundEvent::SoundEvent(AudioSystem* sys, unsigned int id) : mSystem(sys), mID(id){
    
}

SoundEvent::SoundEvent() : mSystem(nullptr), mID(0) {
    
}

void SoundEvent::SetPaused(bool pause){
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if(event) event->setPaused(pause);
}

void SoundEvent::SetVolume(float value) {
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if(event) event->setVolume(value);
}

void SoundEvent::SetPitch(float value) {
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if(event) event->setPitch(value);
}

void SoundEvent::SetParameter(const std::string &name, float value) {
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if (event)
    {
        event->setParameterValue(name.c_str(), value);
    }
}

bool SoundEvent::GetPaused() const {
    bool ret = false;
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if(event) event->getPaused(&ret);
    return ret;
}

float SoundEvent::GetVolume() const {
    float retVal = 0.0f;
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if (event)
    {
        event->getVolume(&retVal);
    }
    return retVal;
}

float SoundEvent::GetPitch() const {
    float retVal = 0.0f;
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if (event)
    {
        event->getPitch(&retVal);
    }
    return retVal;
}

float SoundEvent::GetParameter(const std::string& name){
    float retVal = 0.0f;
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if (event)
    {
        event->getParameterValue(name.c_str(), &retVal);
    }
    return retVal;
}

bool SoundEvent::IsValid(){
    return (mSystem && mSystem->GetEventInstance(mID) != nullptr);
}

void SoundEvent::Stop(bool allowFadeOut /* true */){
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if (event)
    {
        FMOD_STUDIO_STOP_MODE mode = allowFadeOut ?
        FMOD_STUDIO_STOP_ALLOWFADEOUT :
        FMOD_STUDIO_STOP_IMMEDIATE;
        event->stop(mode);
    }
}

// このイベントは3D用か？
bool SoundEvent::Is3D() const {
    bool ret = false;
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    if(event){
        FMOD::Studio::EventDescription* e = nullptr;
        event->getDescription(&e);
        if(e){
            e->is3D(&ret);
        }
    }
    return ret;
}

namespace
{
    FMOD_VECTOR VecToFMOD(const Vector3& in)
    {
        // FMODとこのゲームの座標の方向が違う
        FMOD_VECTOR v;
        v.x = in.y;
        v.y = in.z;
        v.z = in.x;
        return v;
    }
}

// ワールド行列を受け取ってFMODの３D属性に変換。
// イベントの位置と方向を更新するためにアクターのワールド変換を渡す処理が単純化される。
// 行列がワールド空間にあるので、逆行列にする必要はない。 →ここがよくわからない
void SoundEvent::Set3DAttributes(const Matrix4 &worldTrans){
    // このイベントシステムは存在してるか?
    auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
    // さらにイベントインスタンスの存在も確認
    if(event){
        FMOD_3D_ATTRIBUTES attr;
        attr.position = VecToFMOD(worldTrans.GetTranslation());
        // ワールド空間では、第一業が前方
        attr.forward = VecToFMOD(worldTrans.GetXAxis());
        // だ第３業が上
        attr.up = VecToFMOD(worldTrans.GetZAxis());
        attr.velocity = {0.0f,0.0f,0.0f};
        event->set3DAttributes(&attr);
    }
}
