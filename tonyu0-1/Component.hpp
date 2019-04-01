//
//  Component.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/20.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#pragma once
#include <cstdint>

class Component {
public:
    Component(class Actor* owner, int updateOrder = 100);
    virtual ~Component();
    virtual void Update(float deltaTime);
    
    // Input処理 Component独自のProcessInput
    // 子クラスでoverride予定
    virtual void ProcessKeyboard(const uint8_t* Keystate){};
    
    // Getter
    int GetUpdateOrder() const {return mUpdateOrder;}
    
    // OpenGL
    // 親のActorのワールド行列が更新されたら、Componentに通知 (今は仮想関数)
    virtual void OnUpdateWorldTransform(){}
    
protected:
    class Actor* mOwner;
    int mUpdateOrder;
};

// 現在のComponentの種類。全て親Actorの情報にアクセスできる。（座標や回転角など）
// SpriteComponent : 描画すべきSpriteを保持。new時にGame->AddSprite()によりGame->mSpritesに登録される。
// AnimSpriteComponent : SpriteComponentを継承。アニメーション用のUpdate(Componentからの継承)をoverrideしてる。
// BGSpriteComponent : SpriteComponentを継承。背景画像を動かして(Update(from Component))描画する(Draw(from SpriteComponent))
// MoveComponent : 親ActorのPositionやRotationをInputから更新。
// InputComponent : ここで初めてProcessInputをoverride。Inputから継承元のMoveComponentを更新。
