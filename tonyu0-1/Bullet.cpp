//
//  Bullet.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/22.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "Bullet.hpp"
#include "Game.hpp"
#include "MoveComponent.hpp"
#include "SpriteComponent.hpp"
#include "CircleComponent.hpp"
#include "Enemy.hpp"

Bullet::Bullet(class Game* game) : Actor(game), mDeathTimer(1.0f) {
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->LoadTexture("Assets/Laser.png"));
    MoveComponent* mc = new MoveComponent(this);
    mc->SetForwardSpeed(150.0f);
    mCircle = new CircleComponent(this);
    mCircle->SetRadius(11.0f);
}

void Bullet::UpdateActor(float deltaTime){
    mDeathTimer -= deltaTime;
    if(mDeathTimer <= 0.0f){
        SetState(EDead);
    }
//    for (auto enemy : GetGame()->GetEnemies()){
//        if(Intersect(*mCircle, *(enemy->GetCircle()))){
//            SetState(EDead);
//            enemy->SetState(EDead);
//            break;
//        }
//    }
}
