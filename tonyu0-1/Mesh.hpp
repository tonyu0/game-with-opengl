//
//  Mesh.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/29.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <string>
#include <vector>
/* Mesh_hpp */
// メッシュ()を読み込む。
class Mesh {
public:
    Mesh();
    ~Mesh();
    // Gameはテクスチャを配列で保持しているので、読み出そうとしてるテクスチャがGameにロードずみなら、Meshからアクセスできる様にする。
    bool Load(const std::string& fileName, class Game* game);
    bool Unload();
    
    // Getter
    // このメッシュの頂点情報を取得
    class VertexArray* GetVertexArray(){return mVertexArray;}
    // インデックスからテクスチャを取得
    class Texture* GetTexture(size_t index);
    //シェーダー名を取得
    const std::string& GetShaderName() const {return mShaderName;}
    // 境界球の半径を取得（３D空間での当たり判定に使用）
    float GetRadius() const {return mRadius;}
    // 鏡面反射の程度を取得
    float GetSpecPower() const {return mSpecPower;}
    
private:
    std::vector<class Texture*> mTextures; // Meshが使うテクスチャ群
    class VertexArray* mVertexArray;
    std::string mShaderName;
    float mRadius;
    float mSpecPower;
    
};
