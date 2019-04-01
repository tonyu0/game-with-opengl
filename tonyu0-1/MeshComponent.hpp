//
//  MeshComponent.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/29.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#pragma once
#include <stdio.h>
#include "Component.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

// Zバッファ法の擬似コード(OpenGLには実装されている)
// foreach MeshComponent m in scene
//  foreach Pixel p in m
//      float depth = p.Depth()
//      if zBuffer[p.x][p.y] < depth
//          p.draw()

/* MeshComponent_hpp */
class MeshComponent : public Component {
public:
    MeshComponent(class Actor* owner, class Mesh* mesh);
    ~MeshComponent();
    // 渡されたシェーダーでこのMeshを描画
    virtual void Draw(Shader* shader);
    // このコンポーネントが使うMeshとTextureのIDを指定
    virtual void SetMesh(Mesh* mesh){mMesh = mesh;};
    void SetTextureIndex(size_t index);
private:
    class Mesh* mMesh;
    size_t mTextureIndex;
};
