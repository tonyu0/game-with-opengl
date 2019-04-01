//
//  AudioComponent.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/04/01.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "AudioSystem.hpp"
#include "AudioComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"

AudioComponent::AudioComponent(Actor* owner, int updateOrder) : Component(owner,updateOrder) {
    
}

AudioComponent::~AudioComponent(){
    StopAllEvents();
}

// 与えられた名前の
SoundEvent AudioComponent::PlayEvent(const std::string &name){
    // イベントを名前で指定してSoundEventインスタンスを作成
    SoundEvent e = mOwner->GetGame()->GetAudioSystem()->PlayEvent(name);
    // 2D or 3D
    if(e.Is3D()){
        // 3Dだったら追加の設定をする
        mEvent3D.emplace_back(e); // 追加して
        e.Set3DAttributes(mOwner->GetWorldTransform()); // Actorのワールド行列から3D attrを設定。
    } else {
        mEvent2D.emplace_back(e);
    }
    return e;
}

void AudioComponent::Update(float deltaTime){
    Component::Update(deltaTime);
    // 無効（オーディオシステムがないorいベントインスタンスがないSoundEvent）なものを削除
    for(auto itr = mEvent3D.begin(); itr!=mEvent3D.end();++itr){
        if(!itr->IsValid()) mEvent3D.erase(itr);
    }
    
    for(auto itr = mEvent2D.begin(); itr!=mEvent2D.end();++itr){
        if(!itr->IsValid()) mEvent2D.erase(itr);
    }
}

void AudioComponent::OnUpdateWorldTransform(){
    // アクターのワールド行列に更新があったら、サウンドイベント
    Matrix4 world = mOwner->GetWorldTransform();
    for(auto e : mEvent3D){
        if(e.IsValid()){
            e.Set3DAttributes(world);
        }
    }
}

void AudioComponent::StopAllEvents(){
    for(auto e : mEvent3D){
        e.Stop();
    }
    for(auto e : mEvent2D){
        e.Stop();
    }
    mEvent3D.clear();
    mEvent2D.clear();
}
