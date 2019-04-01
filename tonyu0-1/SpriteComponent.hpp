//
//  SpriteComponent.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/20.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#pragma once


#include "Component.hpp"
#include <SDL/SDL.h>

/* SpriteComponent_hpp */

class SpriteComponent : public Component {
public:
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();
    
    virtual void Draw(class Shader* shader);
    
    // Getter
    int GetDrawOrder() const {return mDrawOrder;}
    int GetWidth() const {return mTexWidth;}
    int GetHeight() const {return mTexHeight;}
    
    // Setter
    void SetTexture(class Texture* texture); // mTextureにtextureをset
    
protected:
    class Texture* mTexture;
    int mDrawOrder;
    int mTexWidth;
    int mTexHeight;
};
