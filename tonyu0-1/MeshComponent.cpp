//
//  MeshComponent.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/29.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "VertexArray.hpp"
#include "MeshComponent.hpp"
#include "Texture.hpp"
#include "Actor.hpp"

MeshComponent::MeshComponent(Actor* owner,Mesh* mesh) : Component(owner), mMesh(mesh), mTextureIndex(0) {
    if(mMesh->GetShaderName()=="Phong"){
        mOwner->GetGame()->AddMesh(this);
        SetMesh(mMesh);
    } else if(mMesh->GetShaderName()=="BasicMesh"){
        mOwner->GetGame()->AddBasicMesh(this);
        SetMesh(mMesh);
    }
}

MeshComponent::~MeshComponent(){
    if(mMesh->GetShaderName()=="Phong"){
        mOwner->GetGame()->RemoveMesh(this);
    } else if(mMesh->GetShaderName()=="BasicMesh"){
        mOwner->GetGame()->RemoveBasicMesh(this);
    }
}

void MeshComponent::Draw(Shader* shader){
    if(mMesh){
        // 毎フレーム呼ばれる。描画すべきメッシュが存在すれば、渡ってきたシェーダーのuniformを設定、Mesh
        shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());
        // 鏡面反射のパワー
        shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());
        // メッシュにテクスチャが登録されていたら
        Texture* t = mMesh->GetTexture(mTextureIndex);
        if(t) t->SetActive();
        //メッシュの頂点座標をアクティブに
        VertexArray* va = mMesh->GetVertexArray();
        va->SetActive();
        // 描画
        glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
        
    }
}
