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
#include "Shader.hpp"
#include "Texture.hpp"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) : Component(owner), mDrawOrder(drawOrder), mTexture(nullptr), mTexWidth(0),mTexHeight(0){
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent(){
    mOwner->GetGame()->RemoveSprite(this);
}

// 呼ぶ前にアクティブなVAOとシェーダーが必要。
void SpriteComponent::Draw(Shader* shader){
    if(mTexture){
//        SDL_Rect r;
//        r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
//        r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
//        r.x = static_cast<int>(mOwner->GetPosition().x);
//        r.y = static_cast<int>(mOwner->GetPosition().y);
//
//        SDL_RenderCopyEx(renderer,
//                         mTexture,
//                         nullptr,
//                         &r,
//                         -Math::ToDegrees(mOwner->GetRotation()),
//                         nullptr,
//                         SDL_FLIP_NONE);
        // スケール行列の作成
        Matrix4 scaleMat = Matrix4::CreateScale(static_cast<float>(mTexWidth),static_cast<float>(mTexHeight), 1.0f);
        // ワールド行列の作成
        Matrix4 world = scaleMat * mOwner->GetWorldTransform();
        shader->SetMatrixUniform("uWorldTransform", world);
        // 現在描画中のSpriteのテクスチャをActivate、つまりGPUに読み出し？次のglDrawElementsで描画される。
        mTexture->SetActive();
        // 描画するポリゴン　、　インデックスバッファにあるインデックスの数、インデックスの型、nullptrを指定
        // 上で設定したshaderで描画
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}

void SpriteComponent::SetTexture(Texture* text){
    mTexture = text; // メンバ変数に入れる。
//    SDL_QueryTexture(text, nullptr, nullptr, &mTexWidth, &mTexHeight); // 高さと幅を設定
    mTexHeight = text->GetHeight();
    mTexWidth = text->GetWidth();
}
