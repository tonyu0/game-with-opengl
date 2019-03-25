//
//  Bullet.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/22.
//  Copyright © 2019 Nakagawa. All rights reserved.
//
#pragma once
#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "Actor.hpp"

#endif /* Bullet_hpp */

class Bullet : public Actor{
public:
    Bullet(class Game* game);
    void UpdateActor(float deltaTime) override;
    
private:
    float mDeathTimer;
    class CircleComponent* mCircle;
};
