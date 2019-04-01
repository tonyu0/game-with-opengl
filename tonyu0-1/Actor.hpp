//
//  Actor.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/19.
//  Copyright © 2019 Nakagawa. All rights reserved.
//
#pragma once

#ifndef Actor_hpp
#define Actor_hpp
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
    void ProcessKeyboard(const Uint8* Keystate);
    virtual void ActorInput(const Uint8* Keystate);
    
    // Component management
    void AddComponent(class Component*);
    void RemoveComponent(class Component*);
    
    // Getter
    State GetState() const {return mState;}
    Game* GetGame() const {return mGame;}
    const Vector3& GetPosition() const {return mPosition;}
    float GetScale() const {return mScale;}
    Quaternion GetRotation() const {return mRotation;}
    // 2DでのGetForward() : 平面上でcos and sinを使う。
//    Vector2 GetForward() const {return Vector2(Math::Cos(mRotation),-Math::Sin(mRotation));} // 向いてる向きを返す。
    // 3DでのGetForward() : 元の前方ベクトルにQuaternionを使う。
    Vector3 GetForward() const {return Vector3::Transform(Vector3::UnitX, mRotation);}
    Matrix4 GetWorldTransform() const {return mWorldTransform;}
    
    // Setter 新しい値がセットされたら、ワールド行列を再計算
    void SetState(State state) {mState = state;}
    void SetPosition(Vector3 pos) {mPosition = pos; mRecomputeWorldTransform = true;}
    void SetScale(float scale) {mScale = scale; mRecomputeWorldTransform = true;}
    void SetRotation(Quaternion rot) {mRotation = rot; mRecomputeWorldTransform = true;}
    
    // OpenGL
    void ComputeWorldTransform(); // 呼ばれた時に、ワールド行列を更新。
    
protected:
    // Actorは以下の状態を保つ。
    State mState;
    Vector3 mPosition;
    float mScale;
    Quaternion mRotation; // 回転はQuaternionを使う。
    
    // OpenGL
    // それぞれのActorがもつワールド空間中心からの拡大・回転・移動を合わせた行列
    // スプライトごとにオブジェクト空間を用意してロード、それをワールド空間上で移動することによりメモリの節約。
    // (例えば10個の物体に10個の頂点バッファでは非効率)
    // この行列は頂点シェーダに渡して頂点位置の計算。
    Matrix4 mWorldTransform;
    // UpdateActorなどで、ワールド行列の再計算が必要か？(更新された時のみ行列を再計算)
    bool mRecomputeWorldTransform;
    
    // Components and parent Game
    std::vector<class Component*> mComponents;
    class Game* mGame;
};
