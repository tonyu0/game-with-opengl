//
//  Player.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/21.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "Player.hpp"
#include "AnimSpriteComponent.hpp"
#include "Bullet.hpp"

Player::Player(Game* game):Actor(game), mXSpeed(0.0f), mYSpeed(0.0f) {
    AnimSpriteComponent* asc = new AnimSpriteComponent(this); // Playerに紐付くSpriteComponent
    std::vector<SDL_Texture*> anims = {
        game->LoadTexture("Character01.png"),
        game->LoadTexture("Character02.png"),
        game->LoadTexture("Character03.png"),
        game->LoadTexture("Character04.png"),
        game->LoadTexture("Character05.png"),
        game->LoadTexture("Character06.png"),
    };
    asc->SetAnimTextures(anims);
}

void Player::UpdateActor(float deltaTime){
    Actor::UpdateActor(deltaTime);
    Vector2 pos = GetPosition();
    pos.x += mXSpeed * deltaTime;
    pos.y += mYSpeed * deltaTime;
    
    SetPosition(pos);
}

void Player::ProcessKeyboard(const uint8_t *state){
    mXSpeed = 0.0f;
    mYSpeed = 0.0f;
    if(state[SDL_SCANCODE_UP]){
        mYSpeed -= 200;
    }
    if(state[SDL_SCANCODE_DOWN]){
        mYSpeed += 200;
    }
    if(state[SDL_SCANCODE_LEFT]){
        mXSpeed -= 300;
    }
    if(state[SDL_SCANCODE_RIGHT]){
        mXSpeed += 300;
    }
    
    if(state[SDL_SCANCODE_SPACE]){
        Bullet* bl = new Bullet(GetGame());
        bl->SetPosition(GetPosition());
        bl->SetRotation(GetRotation());
        
    }
}
