//
//  CircleComponent.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/22.
//  Copyright © 2019 Nakagawa. All rights reserved.
//
#pragma once
#ifndef CircleComponent_hpp
#define CircleComponent_hpp

#include "Math.hpp"
#include "Component.hpp"

#endif /* CircleComponent_hpp */

class CircleComponent : public Component{
public:
    CircleComponent(class Actor* owner);
    
    // Setter
    void SetRadius(float rad){mRadius = rad;}
    
    // Getter
    float GetRadius() const;
    const Vector3& GetCenter() const;
private:
    float mRadius;
};

bool Intersect(const CircleComponent& a, const CircleComponent& b);
