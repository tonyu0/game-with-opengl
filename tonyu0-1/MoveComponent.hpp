//
//  MoveComponent.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/22.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#pragma once
#ifndef MoveComponent_hpp
#define MoveComponent_hpp

#include <stdio.h>
#include "Component.hpp"

#endif /* MoveComponent_hpp */

// 動くが操作はしないActorはこれをAdd。動きをベクトルと角度で表す。
class MoveComponent : public Component {
public:
    MoveComponent(class Actor* owner, int updateOrder = 10);
    void Update(float deltaTime) override;
    
    // Setter
    void SetForwardSpeed(float speed){mForwardSpeed = speed;}
    void SetAngularSpeed(float speed){mAngularSpeed = speed;}
    
    // Getter
    float GetForwardSpeed() const {return mForwardSpeed;}
    float GetAngularSpeed() const {return mAngularSpeed;}
    
private:
    float mForwardSpeed;
    float mAngularSpeed;
};
