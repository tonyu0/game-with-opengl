//
//  CircleComponent.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/22.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "CircleComponent.hpp"
#include "Actor.hpp"

CircleComponent::CircleComponent(Actor* owner) : Component(owner), mRadius(0.0f) {
    
}

const Vector3& CircleComponent::GetCenter() const {
    return mOwner->GetPosition();
}

float CircleComponent::GetRadius() const {
    return mOwner->GetScale() * mRadius;
}

bool Intersect(const CircleComponent& a, const CircleComponent& b){
    Vector3 diff = a.GetCenter() - b.GetCenter();
    float distSq = diff.LengthSq();
    
    float radiiSq = a.GetRadius() + b.GetRadius();
    radiiSq *= radiiSq;
    return distSq <= radiiSq;
}
