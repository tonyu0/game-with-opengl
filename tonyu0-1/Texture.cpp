//
//  Texture.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/25.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "Texture.hpp"
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <SDL/SDL.h>

Texture::Texture() : mTextureID(0), mHeight(0), mWidth(0){
    
}

Texture::~Texture(){
    
}

bool Texture::Load(const std::string &fileName){
    
    int channels = 0;
    
    // 画像ファイルの読み込み　ファイル名、幅、高さ、チャネル数が変数に記録される
    unsigned char* image = SOIL_load_image(fileName.c_str(),
                                           &mWidth, &mHeight, &channels, SOIL_LOAD_AUTO);
    
    if (image == nullptr)
    {
        SDL_Log("SOIL failed to load image %s: %s", fileName.c_str(), SOIL_last_result());
        return false;
    }
    
    // チャネル数でっ場合分け
    int format = GL_RGB;
    if (channels == 4)
    {
        format = GL_RGBA;
    }
    
    // 空いてるテクスチャIDを検索
    glGenTextures(1, &mTextureID);
    // テクスチャをGPUのVRAMにUP (OpenGLテクスチャオブジェクトを作成)
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    // 生の画像データをコピー
    glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format,
                 GL_UNSIGNED_BYTE, image);
    // OpenGLにコピーしたらSOIL画像データはっメモリから解放
    SOIL_free_image_data(image);
    
    // バイリニア補完
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    return true;
}

void Texture::Unload(){
    glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive(){
    // ここをGL_TEXTUREに設定してたせいでテクスチャが１種類しか読めない状態になってた : 所要時間1日
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}
