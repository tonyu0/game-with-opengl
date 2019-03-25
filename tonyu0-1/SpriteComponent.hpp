//
//  SpriteComponent.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/20.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#pragma once

#ifndef SpriteComponent_hpp
#define SpriteComponent_hpp

#include "Component.hpp"
#include "SDL2/SDL.h"

#endif /* SpriteComponent_hpp */

class SpriteComponent : public Component {
public:
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();
    
    virtual void Draw(SDL_Renderer* renderer);
    
    // Getter
    int GetDrawOrder() const {return mDrawOrder;}
    int GetWidth() const {return mTexWidth;}
    int GetHeight() const {return mTexHeight;}
    
    // Setter
    void SetTexture(SDL_Texture* texture); // mTextureにtextureをset
    
protected:
    SDL_Texture* mTexture;
    int mDrawOrder;
    int mTexWidth;
    int mTexHeight;
};
