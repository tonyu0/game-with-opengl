//
//  SpriteComponent.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/20.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "SpriteComponent.hpp"
#include "Actor.hpp"
#include "Game.hpp"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) : Component(owner), mDrawOrder(drawOrder), mTexture(nullptr){
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent(){
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer){
    if(mTexture){
        SDL_Rect r;
        r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
        r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
        r.x = static_cast<int>(mOwner->GetPosition().x);
        r.y = static_cast<int>(mOwner->GetPosition().y);
        
        SDL_RenderCopyEx(renderer,
                         mTexture,
                         nullptr,
                         &r,
                         -Math::ToDegrees(mOwner->GetRotation()),
                         nullptr,
                         SDL_FLIP_NONE);
    }
}

void SpriteComponent::SetTexture(SDL_Texture* text){
    mTexture = text; // メンバ変数に入れる。
    SDL_QueryTexture(text, nullptr, nullptr, &mTexWidth, &mTexHeight); // 高さと幅を設定
}
