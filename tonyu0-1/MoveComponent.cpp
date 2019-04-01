//
//  MoveComponent.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/22.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "MoveComponent.hpp"
#include "Actor.hpp"

MoveComponent::MoveComponent(Actor* owner,int updateOrder) : Component(owner, updateOrder), mForwardSpeed(0.0f), mAngularSpeed(0.0f){
    
}

void MoveComponent::Update(float deltaTime){
    // update position
    Vector3 pos = mOwner->GetPosition();
    pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
//    if (pos.x < -512.0f) { pos.x = 512.0f; }
//    else if (pos.x > 512.0f) { pos.x = -512.0f; }
//
//    if (pos.y < -384.0f) { pos.y = 384.0f; }
//    else if (pos.y > 384.0f) { pos.y = -384.0f; }
    mOwner->SetPosition(pos);
    
    // 3D空間での回転は、Quaternionを使用
    // 現時点ではZ軸を上にして倒れずに回転
    Quaternion rot = mOwner->GetRotation();
    Quaternion add(Vector3::UnitZ,mAngularSpeed * deltaTime); // Z軸周りの回転を表すQuaternion
    rot = Quaternion::Concatenate(rot, add);
    mOwner->SetRotation(rot);
}
