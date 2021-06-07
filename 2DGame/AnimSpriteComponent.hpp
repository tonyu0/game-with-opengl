//
//  AnimSpriteComponent.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/21.
//  Copyright © 2019 Nakagawa. All rights reserved.
//
#pragma once
#ifndef AnimSpriteComponent_hpp
#define AnimSpriteComponent_hpp

#include "SpriteComponent.hpp"
#include <vector>

#endif /* AnimSpriteComponent_hpp */

class AnimSpriteComponent : public SpriteComponent {
public:
  AnimSpriteComponent(class Actor *owner, int drawOrder = 100);
  // フレームごとにアニメを更新
  void Update(float deltaTime) override;
  void SetAnimTextures(const std::vector<SDL_Texture *> &textures);

private:
  std::vector<SDL_Texture *> mAnimTextures;
  float mCurFrame;
  float mAnimFPS;
};
