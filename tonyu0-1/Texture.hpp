//
//  Texture.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/25.
//  Copyright © 2019 Nakagawa. All rights reserved.
//
#pragma once

#ifndef Texture_hpp
#define Texture_hpp

#include <string>

#endif /* Texture_hpp */

// テクスチャごとにこのクラスを作成
// 一度読めば、あとはワールド変換で複数作ることができる。
class Texture{
public:
    Texture();
    ~Texture();
    
    bool Load(const std::string& filename);
    void Unload();
    
    void SetActive();
    
    // Getter
    int GetHeight() const {return mHeight;}
    int GetWidth() const { return mWidth;}
    
private:
    // OpenGLのテクスチャID
    unsigned int mTextureID;
    int mHeight;
    int mWidth;
};
