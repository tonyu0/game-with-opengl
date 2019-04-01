//
//  AnimSpriteComponent.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/21.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "AnimSpriteComponent.hpp"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder) : SpriteComponent(owner,drawOrder), mCurFrame(0.0f), mAnimFPS(24.0f){
    
}

void AnimSpriteComponent::Update(float deltaTime){
//    SpriteComponent::Update(deltaTime);
//    mCurFrame += mAnimFPS * deltaTime;
//    if(mCurFrame >= mAnimTextures.size()){
//        mCurFrame -= mAnimTextures.size();
//    }
//    SetTexture(mAnimTextures[static_cast<int>(mCurFrame)]);
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& anims){
//    mAnimTextures = anims;
//    if(mAnimTextures.size()>0){
//        mCurFrame = 0.0f;
//        SetTexture(mAnimTextures[0]);
//    }
}
