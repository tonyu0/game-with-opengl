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
#include "Math.hpp"

Enemy::Enemy(Game* game) : Actor(game) {
    Vector3 randPos = Random::GetVector(Vector3(-512.0f, -384.0f,0.f),
                                        Vector3(512.0f, 384.0f,0.f));
    SetPosition(randPos);
    
    SetRotation(Quaternion(Vector3::UnitX,Random::GetFloatRange(0.0f, Math::TwoPi)));
    
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->LoadTexture("Assets/s_kao.png"));
    
    MoveComponent* mc = new MoveComponent(this);
    mc->SetForwardSpeed(150.0f);
    
    mCircle = new CircleComponent(this);
    mCircle->SetRadius(10.0f);
    
    GetGame()->AddEnemy(this);
}

Enemy::~Enemy(){
    GetGame()->RemoveEnemy(this);
}
