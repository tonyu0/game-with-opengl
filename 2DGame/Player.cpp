//
//  Player.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/21.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "Player.hpp"
#include "SpriteComponent.hpp"
#include "InputComponent.hpp"
#include "Bullet.hpp"

Player::Player(Game* game):Actor(game), mCircle(nullptr) {
//    AnimSpriteComponent* asc = new AnimSpriteComponent(this); // Playerに紐付くSpriteComponent
//    std::vector<SDL_Texture*> anims = {
//        game->LoadTexture("Character01.png"),
//        game->LoadTexture("Character02.png"),
//        game->LoadTexture("Character03.png"),
//        game->LoadTexture("Character04.png"),
//        game->LoadTexture("Character05.png"),
//        game->LoadTexture("Character06.png"),
//    };
//    asc->SetAnimTextures(anims);
    // SpriteComponentにテクスチャをセット
//    SpriteComponent* sc = new SpriteComponent(this, 150);
//    sc->SetTexture(game->LoadTexture("Assets/Ship.png"));
    
    // InputComponent
    InputComponent* ic = new InputComponent(this);
    ic->SetForwardSpeed(60.0f);
    ic->SetAngularSpeed(10.f);
    
}

void Player::UpdateActor(float deltaTime){
    Actor::UpdateActor(deltaTime);
        
    // ビュー行列はあカメラの位置、向いてる方向、上方向から作れる。
    Vector3 cameraPos = GetPosition();
    Vector3 target = GetPosition() + GetForward() * 100.0f;
    Vector3 up = Vector3::UnitZ;
    
    // ビュー行列　カメラの目の位置と、向いている方向
    Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
    GetGame()->SetViewMatrix(view);
}

// Player独自の動き（射出）をここでオーバーライド。
void Player::ActorInput(const uint8_t *state){
//    if(state[SDL_SCANCODE_SPACE]){
//        Bullet* bl = new Bullet(GetGame());
//        bl->SetPosition(GetPosition());
//        bl->SetRotation(GetRotation());
//    }
}
