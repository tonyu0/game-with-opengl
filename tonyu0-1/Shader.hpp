//
//  Shader.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/25.
//  Copyright © 2019 Nakagawa. All rights reserved.
//
#pragma once

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <string>
#include "Math.hpp"
#include <GL/glew.h>

#endif /* Shader_hpp */

// Shader : 指定した頂点シェーダ、フラグメントシェーダの組を
// やること
// 1, 頂点シェーダーをロードしてコンパイル
// 2, フラグメントシェーダーをロードしてコンパイル
// 3, 2つのシェーダーをリンクして「シェーダープログラム」にする。

class Shader {
public:
    Shader();
    ~Shader();
    // シェーダ読み込み
    bool Load(const std::string& vertShader,const std::string& fragShader);
    // シェーダプログラムをアクティブに。
    void SetActive();
    
    void Unload();
    // Sets a Matrix uniform
    void SetMatrixUniform(const char* name, const Matrix4& matrix);
    void SetVectorUniform(const char* name, const Vector3& vector);
    void SetFloatUniform(const char* name, const float f);
private:
    
    // Loadのヘルパー関数　：　し
    bool CompileShader(const std::string& filename, GLenum shaderType, GLuint& outShader);
    // Tests whether shader compiled successfully
    bool IsCompiled(GLuint shader);
    // Tests whether vertex/fragment programs link
    bool IsValidProgram();
    
    
    GLuint mVertShader;
    GLuint mFragShader;
    GLuint mShader;
};

