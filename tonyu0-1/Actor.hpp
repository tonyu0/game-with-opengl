//
//  Actor.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/19.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#ifndef Actor_hpp
#define Actor_hpp

#pragma once
#include <stdio.h>
#include <vector>
#include "Game.hpp"
#include "Math.hpp"

#endif /* Actor_hpp */

class Actor {
public:
    enum State{
        EActive,
        EPause,
        EDead
    };
    Actor(Game *game); // dependency injection - Game内の機能にActorがアクセスできるようになる。
    virtual ~Actor();
    
    // Updateが3種類！　UpdateActorのみけ子クラスでのoverrideができる。
    void Update(float deltaTime); // Gameから呼び出される。
    void UpdateComponents(float deltaTime); // 全コンポ年とを更新
    virtual void UpdateActor(float deltaTime); //
    
    // Input処理 キーの処理を受け取り、動かす。
    void ProcessInput(const int* Keystate);
    virtual void ActorInput(const int* Keystate);
    
    // Component management
    void AddComponent(class Component*);
    void RemoveComponent(class Component*);
    
    // Getter
    State GetState() const {return mState;}
    Game* GetGame() const {return mGame;}
    const Vector2& GetPosition() const {return mPosition;}
    float GetScale() const {return mScale;}
    float GetRotation() const {return mRotation;}
    Vector2 GetForward() const {return Vector2(Math::Cos(mRotation),-Math::Sin(mRotation));} // 向いてる向きを返す。
    
    // Setter
    void SetState(State state) {mState = state;}
    void SetPosition(Vector2 pos) {mPosition = pos;}
    void SetScale(float scale) {mScale = scale;}
    void SetRotation(float rot) {mRotation = rot;}
    
protected:
    // Actorは以下の状態を保つ。
    State mState;
    Vector2 mPosition;
    float mScale;
    float mRotation;
    
    // Components and parent Game
    std::vector<class Component*> mComponents;
    class Game* mGame;
};
