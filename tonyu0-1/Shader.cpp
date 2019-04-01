//
//  Shader.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/25.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "Shader.hpp"
#include <SDL/SDL.h>
#include <fstream>
#include <sstream>

Shader::Shader()
: mShader(0)
, mVertShader(0)
, mFragShader(0)
{
    
}

Shader::~Shader()
{
    
}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
    // Compile vertex and pixel shaders
    if (!CompileShader(vertName,
                       GL_VERTEX_SHADER,
                       mVertShader) ||
        !CompileShader(fragName,
                       GL_FRAGMENT_SHADER,
                       mFragShader))
    {
        return false;
    }
    
    // Now create a shader program that
    // links together the vertex/frag shaders
    mShader = glCreateProgram();
    glAttachShader(mShader, mVertShader);
    glAttachShader(mShader, mFragShader);
    glLinkProgram(mShader);
    
    // Verify that the program linked successfully
    if (!IsValidProgram())
    {
        return false;
    }
    
    return true;
}

void Shader::Unload()
{
    // Delete the program/shaders
    glDeleteProgram(mShader);
    glDeleteShader(mVertShader);
    glDeleteShader(mFragShader);
}

void Shader::SetActive()
{
    // Set this program as the active one
    glUseProgram(mShader);
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
    // uniform "name" (シェーダ上にて)
    GLuint loc = glGetUniformLocation(mShader, name);
    // Send the matrix data to the uniform
    // loc(uniform ID)に1個の行列を、行ベクトルにかかけるために呼ぶ。
    glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
    // いちいち問い合わせてるが、 uniform ID は実行中に変わるものではないから、これをキャッシュしておくことで性能を改善できる。
    // uniform buffer object(UBO)はuniformをグループ化できるが、万全ではないため使用しない。
    // グループ分けの利点　：　例えばビュー射影行列は１フレームに一回だが、ワールド行列はActorごとに異なる。
}

void Shader::SetVectorUniform(const char *name, const Vector3 &vector){
    GLuint loc = glGetUniformLocation(mShader, name);
    glUniform3fv(loc, 1, vector.GetAsFloatPtr());
}

void Shader::SetFloatUniform(const char *name, const float f){
    GLuint loc = glGetUniformLocation(mShader, name);
    glUniform1f(loc, f);
}

// file名・vert or fragを受け取り、outShaderにコンパイル後のIDを格納
bool Shader::CompileShader(const std::string& fileName,
                           GLenum shaderType,
                           GLuint& outShader)
{
    // Open file
    std::ifstream shaderFile(fileName);
    if (shaderFile.is_open())
    {
        // Read all the text into a string
        std::stringstream sstream;
        sstream << shaderFile.rdbuf();
        std::string contents = sstream.str();
        const char* contentsChar = contents.c_str();
        
        // Create a shader of the specified type
        outShader = glCreateShader(shaderType);
        // Set the source characters and try to compile
        glShaderSource(outShader, 1, &(contentsChar), nullptr);
        glCompileShader(outShader);
        
        if (!IsCompiled(outShader))
        {
            SDL_Log("Failed to compile shader %s", fileName.c_str());
            return false;
        }
    }
    else
    {
        SDL_Log("Shader file not found: %s", fileName.c_str());
        return false;
    }
    
    return true;
}

bool Shader::IsCompiled(GLuint shader)
{
    GLint status;
    // シェーダーの状態をstatusに格納
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if (status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        SDL_Log("GLSL Compile Failed:\n%s", buffer);
        return false;
    }
    
    return true;
}

bool Shader::IsValidProgram()
{
    
    GLint status;
    // シェーダープログラムの状態をstatusに格納
    glGetProgramiv(mShader, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetProgramInfoLog(mShader, 511, nullptr, buffer);
        SDL_Log("GLSL Link Status:\n%s", buffer);
        return false;
    }
    
    return true;
}
