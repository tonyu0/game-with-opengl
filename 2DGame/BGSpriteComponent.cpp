//
//  BGSpriteComponent.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/21.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "BGSpriteComponent.hpp"
#include "Actor.hpp"

BGSpriteComponent::BGSpriteComponent(class Actor *owner, int drawOrder)
    : SpriteComponent(owner, drawOrder), mScrollSpeed(0.0f) {}

void BGSpriteComponent::Update(float deltaTime) {
  SpriteComponent::Update(deltaTime);
  for (auto &tex : mBGTextures) {
    tex.Offset.x += mScrollSpeed * deltaTime;
    if (tex.Offset.x < -mScreenSize.x) {
      tex.Offset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
    }
  }
}

void BGSpriteComponent::SetBGTextures(
    const std::vector<SDL_Texture *> &textures) {
  int count = 0;
  for (auto tex : textures) {
    BGTexture temp;
    temp.mTexture = tex;
    temp.Offset.x = count * mScreenSize.x;
    temp.Offset.y = 0;
    mBGTextures.emplace_back(temp);
    count++;
  }
}

void BGSpriteComponent::Draw(SDL_Renderer *renderer) {
  for (auto &tex : mBGTextures) {
    SDL_Rect r;
    r.w = static_cast<int>(mScreenSize.x);
    r.h = static_cast<int>(mScreenSize.y);
    r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2 + tex.Offset.x);
    r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2 + tex.Offset.y);

    SDL_RenderCopy(renderer, tex.mTexture, nullptr, &r);
  }
}
