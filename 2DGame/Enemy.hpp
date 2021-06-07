//
//  Enemy.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/22.
//  Copyright © 2019 Nakagawa. All rights reserved.
//
#pragma once
#ifndef Enemy_hpp
#define Enemy_hpp

#include "Game.hpp"
#include "Actor.hpp"

#endif /* Enemy_hpp */

class Enemy : public Actor {
public:
    Enemy(class Game* game);
    ~Enemy();
    class CircleComponent* GetCircle() {return mCircle;}
private:
    class CircleComponent* mCircle;
};
