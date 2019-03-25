//
//  VertexArray.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/23.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

#include <stdio.h>

#endif /* VertexArray_hpp */

class VertexArray{
public:
    VertexArray(const float* vertices, unsigned int numVertices, const float* indices, unsigned int numIndices);
    ~VertexArray();
    
    void SetActive();
    
private:
    unsigned int mNumVertices;
    unsigned int mNumIndices;
    unsigned int mVertexBuffer; // 頂点バッファのOpenGL ID
    unsigned int mIndexBuffer; // インデックスバッファのOpenGL ID
    unsigned int mVertexArray; // VAOの ID
    
};
