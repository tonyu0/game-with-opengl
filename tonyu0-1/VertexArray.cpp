//
//  VertexArray.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/23.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "VertexArray.hpp"
#include <GL/glew.h>


VertexArray::VertexArray(const float* vertices, unsigned int numVertices, const unsigned int* indices, unsigned int numIndices) : mNumVertices(numVertices), mNumIndices(numIndices){
    
    // Vertex array生成
    // メンバ変数に1つのVAOを作成
    glGenVertexArrays(1, &mVertexArray);
    glBindVertexArray(mVertexArray);
    
    // 頂点バッファ
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    // UV座標追加で、ここの頂点が5個のfloatを持つ。
    glBufferData(
         GL_ARRAY_BUFFER,
         numVertices * 8 * sizeof(float),
         vertices,
         GL_STATIC_DRAW // GPUでデータのロードを１回だけ行い、描画で頻繁にデータを読み込む際に使用。
    );
    
    // インデックスバッファ
    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        numIndices * sizeof(float),
        indices,
        GL_STATIC_DRAW
    );
    
    // 頂点レイアウト　ー　モデルの各頂点のデータ形式
    glEnableVertexAttribArray(0); // 頂点レイアウトをう有効か
    glVertexAttribPointer( // 1個目の頂点属性　ー　頂点座標
        0, // 属性インデックス
        3, // 成分の数
        GL_FLOAT,
        GL_FALSE,
        sizeof(float) * 8, // ストライド -
        0 // 頂点データの開始位置からこの属性までのオフセット
    );
    
    glEnableVertexAttribArray(1); // 2個目の頂点属性　ー　法線情報
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(float) * 8,reinterpret_cast<void*>(sizeof(float) * 3)
    );
    
    glEnableVertexAttribArray(2); // 3個目の頂点情報　ー　uv座標
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void*>(sizeof(float)*6));
    
    
    
}

VertexArray::~VertexArray(){
    glDeleteBuffers(1,&mIndexBuffer);
    glDeleteBuffers(1,&mVertexBuffer);
    glDeleteVertexArrays(1,&mVertexArray);
}

void VertexArray::SetActive(){
    glBindVertexArray(mVertexArray);
}
