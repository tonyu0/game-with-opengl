//
//  BGSpriteComponent.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/21.
//  Copyright © 2019 Nakagawa. All rights reserved.
//
#pragma once
#ifndef BGSpriteComponent_hpp
#define BGSpriteComponent_hpp

#include "Math.hpp"
#include "SpriteComponent.hpp"
#include <vector>


#endif /* BGSpriteComponent_hpp */

class BGSpriteComponent : public SpriteComponent {
public:
  BGSpriteComponent(class Actor *owner, int drawOrder = 10);
  void Update(float deltaTime) override;
  void Draw(SDL_Renderer *renderer);

  // Setter
  void SetBGTextures(const std::vector<SDL_Texture *> &textures);
  void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
  void SetScreenSize(const Vector2 &size) { mScreenSize = size; }
  float GetScrollSpeed() const { return mScrollSpeed; }

private:
  struct BGTexture {
    Vector2 Offset;
    SDL_Texture *mTexture;
  };
  std::vector<BGTexture> mBGTextures;
  Vector2 mScreenSize;
  float mScrollSpeed;
};
