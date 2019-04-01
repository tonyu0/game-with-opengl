//
//  Game.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/19.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#pragma once

#ifndef Game_hpp
#define Game_hpp

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <vector>
#include <unordered_map>
#include "Math.hpp"
#include "SoundEvent.hpp"

#endif /* Game_hpp */

// 光
struct DirectionalLight {
    // 光の方向
    Vector3 mDirection;
    // 光の拡散反射色
    Vector3 mDiffuseColor;
    // 光の鏡面反射色
    Vector3 mSpecColor;
};

class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void ShutDown();
    
    // Actor
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);
    std::vector<class Enemy*>& GetEnemies(){return mEnemies;}
    void AddEnemy(class Enemy* enemy);
    void RemoveEnemy(class Enemy* enemy);
    
    // Sprite
    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);
    // Mesh
    void AddMesh(class MeshComponent* mesh);
    void RemoveMesh(class MeshComponent* mesh);
    void AddBasicMesh(class MeshComponent* mesh);
    void RemoveBasicMesh(class MeshComponent* mesh);
    
    
    //Texture
    class Texture* LoadTexture(const std::string& filename);
    //Mesh
    class Mesh* LoadMesh(const std::string& filename);
    
    // Set various matrix
    // だいたいPlayerから使われる。
    void SetViewMatrix(Matrix4 view){mView = view;}
    void SetProjMatrix(Matrix4 proj){mProj = proj;}
    
    // オーディオ関連
    class AudioSystem* GetAudioSystem(){return mAudioSystem;}
    
private:
    void Input();
    void Update();
    void Output();
    
    // VertexArray
    void CreateSpriteVertices();
    bool LoadShaders();
    
    // 押されたボタンで場合分け
    void HandleKeyPress(int key);
    
    // Phongシェーダーの光源uniformの設定
    void SetLightUniforms(class Shader* shader);
    

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    
    // mTextures : map<filename, class Texture*>
    std::unordered_map<std::string, class Texture*> mTextures;
    // mMeshes : map<filaname, class Mesh*>
    std::unordered_map<std::string, class Mesh*> mMeshes;
    
    bool mIsRunning;
    int mTicksCount;
    // 物体管理
    class Player* mPlayer;
    
    // Actor manegement
    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;
    bool mUpdatingActor;
    
    // 描画するスプライトコンポーネント（2D）を保持　→ 親Actorの座標から描画するコンポーネント
    std::vector<class SpriteComponent*> mSpriteComps;
    // 描画するメッシュコンポーネント（3D）を保持　→ 親Actorの座標から描画するコンポーネント
    std::vector<class MeshComponent*> mMeshComps;
    std::vector<class MeshComponent*> mBasicMeshComps;
    
    std::vector<class Enemy*> mEnemies;
    
    //// OpenGL
    SDL_GLContext mContext;
    class VertexArray* mSpriteVertices;
    // Sprite用のシェーダー
    class Shader* mSpriteShader;
    // Mesh用のシェーダー
    class Shader* mMeshShader;
    class Shader* mBasicMeshShader;
    Matrix4 mView; // ビュー行列
    Matrix4 mProj; // 射影行列
    
    // Phong shader
    Vector3 mAmbientLight;
    DirectionalLight mDirLight;
    
    //// オーディオ
    class AudioSystem* mAudioSystem; // おそらくゲームに一つ
    SoundEvent mMusicEvent; // 音楽
    SoundEvent mReverbSnap; // リバーブを有効・無効に調整するためのスナップショット
};
