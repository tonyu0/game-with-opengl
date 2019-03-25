//
//  Component.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/20.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "Component.hpp"
#include "Actor.hpp"

Component::Component(Actor* owner,int updateOrder) : mOwner(owner), mUpdateOrder(updateOrder) {
    mOwner->AddComponent(this);
}

Component::~Component(){
    mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime){
    
}
