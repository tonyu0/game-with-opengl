//
//  Enemy.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/22.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "Enemy.hpp"
#include "Random.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "CircleComponent.hpp"

Enemy::Enemy(Game* game) : Actor(game) {
    Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f,768.0f));
    SetPosition(randPos);
    
    SetRotation(Random::GetFloatRange(0, Math::TwoPi));
    
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->LoadTexture("s_kao.png"));
    
    MoveComponent* mc = new MoveComponent(this);
    mc->SetForwardSpeed(150.0f);
    
    mCircle = new CircleComponent(this);
    mCircle->SetRadius(10.0f);
    
    GetGame()->AddEnemy(this);
}

Enemy::~Enemy(){
    GetGame()->RemoveEnemy(this);
}
