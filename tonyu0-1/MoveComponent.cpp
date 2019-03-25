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
    Vector2 pos = mOwner->GetPosition();
    pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
    if (pos.x < 0.0f) { pos.x = 1022.0f; }
    else if (pos.x > 1024.0f) { pos.x = 2.0f; }
    
    if (pos.y < 0.0f) { pos.y = 766.0f; }
    else if (pos.y > 768.0f) { pos.y = 2.0f; }
    mOwner->SetPosition(pos);
    
    
    float rot = mOwner->GetRotation();
    rot += mAngularSpeed * deltaTime;
    mOwner->SetRotation(rot);
}
