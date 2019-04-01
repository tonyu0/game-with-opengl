//
//  Game.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/19.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "Game.hpp"
#include "Actor.hpp"
#include "SpriteComponent.hpp"
#include "MeshComponent.hpp"
#include "AudioComponent.hpp"
#include "BGSpriteComponent.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "AudioSystem.hpp"
#include <GL/glew.h>

// 処理の順番　：　描画関連　→ サウンド関連

Game::Game() : mWindow(nullptr),mAudioSystem(nullptr), mSpriteShader(nullptr), mIsRunning(true), mTicksCount(0) {
    
}

bool Game::Initialize(){
    // 映像と音で初期化
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
        SDL_Log("Error : %s",SDL_GetError());
        return false;
    }
    
    // Setting OpenGL Window Attr
    // Using Core OpenGL profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // Using OpenGL 3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    // Color Buffer setting (8bit)
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // Enable Double buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // OpenGL use Graphics hardware(GPU)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    
    // create_window
    mWindow = SDL_CreateWindow("Title", 100, 100, 1024, 768, SDL_WINDOW_OPENGL);
    if(!mWindow){
        SDL_Log("Failed to make window : %s",SDL_GetError());
        return false;
    }
    
    // create GLcontext
    mContext = SDL_GL_CreateContext(mWindow);
    glewExperimental = GL_TRUE; // this seems prevent initialization error in some platforms
    if(glewInit() != GLEW_OK){
        SDL_Log("Failed to initialize GLEW : %s", SDL_GetError());
        return false;
    }
    glGetError();
    
    // create AudioSystem
    mAudioSystem = new AudioSystem(this);
    if(!mAudioSystem->Initialize()){
        SDL_Log("Failed to initialize audio system.");
        mAudioSystem->ShutDown();
        delete mAudioSystem;
        mAudioSystem = nullptr;
        return false;
    }
    
    
    // シェーダーの読み込み
    if(!LoadShaders()){
        SDL_Log("Failed to load shaders.");
        return false;
    }
    // VAOの作成
    CreateSpriteVertices();
    
    // Renderer : シェーダーに交代
    // 第二引数　：　グラフィックスDriver マルチウインドウの時に意味がある。
//    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    if(!mRenderer){
//        SDL_Log("Failed to make Renderer : %s",SDL_GetError());
//    }
    
    // IMG_Loadなど : SOILに交代
//    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
//    {
//        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
//        return false;
//    }
    
    mPlayer = new Player(this);
    mPlayer->SetPosition(Vector3(10.0f,100.0f,0.f));
    mPlayer->SetScale(1.5f);
//    Actor* bg = new Actor(this);
//    bg->SetPosition(Vector2(512,384));
//    BGSpriteComponent* bgcomp = new BGSpriteComponent(bg);
//
//    bgcomp->SetScreenSize(Vector2(1024.0f,768.0f));
//    std::vector<SDL_Texture*> bgtextures = {
//        LoadTexture("Farback01.png"),
//        LoadTexture("Farback02.png"),
//    };
//    bgcomp->SetBGTextures(bgtextures);
//    bgcomp->SetScrollSpeed(-100.0f);
//
//    bgcomp = new BGSpriteComponent(bg,50);
//    bgtextures = {
//        LoadTexture("Stars.png"),
//        LoadTexture("Stars.png")
//    };
//    bgcomp->SetScreenSize(Vector2(1024.0f, 768.0f));
//    bgcomp->SetBGTextures(bgtextures);
//    bgcomp->SetScrollSpeed(-200.0f);
//
//    for(int i=0;i<20;++i){
//        new Enemy(this);
//    }
//
//
    // Create actors
    Actor* a = new Actor(this);
    a->SetPosition(Vector3(200.0f, 75.0f, 0.0f));
    a->SetScale(100.0f);
    Quaternion q(Vector3::UnitY, -Math::PiOver2);
    q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
    a->SetRotation(q);
    MeshComponent* mc = new MeshComponent(a,LoadMesh("Assets/Cube.gpmesh"));
    
    a = new Actor(this);
    a->SetPosition(Vector3(200.0f, -75.0f, 0.0f));
    a->SetScale(3.0f);
    mc = new MeshComponent(a,LoadMesh("Assets/Sphere.gpmesh"));
    AudioComponent* ac = new AudioComponent(a);
    ac->PlayEvent("event:/FireLoop");
    
    
    a = new Actor(this);
    a->SetPosition(Vector3(500.0f, -125.0f, 0.0f));
    a->SetScale(10.0f);
    mc = new MeshComponent(a,LoadMesh("Assets/Sphere.gpmesh"));
    
    a = new Actor(this);
    a->SetPosition(Vector3(400.0f,400.0f,0.0f));
    a->SetScale(2.0f);
    SpriteComponent* sc = new SpriteComponent(a);
    sc->SetTexture(LoadTexture("Assets/s_kao.png"));
    
//    // Setup floor
    const float start = -1250.0f;
    const float size = 250.0f;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            a = new Actor(this);
            a->SetPosition(Vector3(start + i * size, start + j * size, -100.0f));
            a->SetScale(10.0f);
            mc = new MeshComponent(a,LoadMesh("Assets/Plane.gpmesh"));
        }
    }
    
    // Setup lights
    mAmbientLight = Vector3(0.2f, 0.2f, 0.2f);
    mDirLight.mDirection = Vector3(0.0f, -0.707f, -0.707f);
    mDirLight.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
    mDirLight.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
    
    // UI
//    a = new Actor(this);
//    a->SetPosition(Vector3(-350.0f, -350.0f, 0.0f));
//    SpriteComponent* sc = new SpriteComponent(a);
//    sc->SetTexture(LoadTexture("Assets/s_kao.png"));
    
    return true;
}

void Game::RunLoop(){
    while(mIsRunning){
        Input();
        Update();
        Output();
    }
}

void Game::ShutDown(){
    // Audio
    mAudioSystem->ShutDown();
    
    // Destroy
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);
    
    // Quit IMG
//    IMG_Quit();
    // Quit SDL
    SDL_Quit();
}

void Game::Input(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type){
            case SDL_QUIT:
                mIsRunning = false;
                break;
            case SDL_KEYDOWN:
                if (!event.key.repeat)
                {
                    HandleKeyPress(event.key.keysym.sym);
                }
                break;
        }
    }
    
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_ESCAPE]){
        mIsRunning = false;
    }
    
    // Playerなど、入力を受け付けるもの
    mUpdatingActor = true;
    for(auto actor : mActors){
        actor->ProcessKeyboard(state);
    }
    mUpdatingActor = false;
}

void Game::Update(){
    // Calculate deltaTime
    // 物理法則で動くゲームではフレームレートによって挙動が変わる。
    // so until target deltaTime pass, wait with stopping game loop
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    mTicksCount = SDL_GetTicks();
    
    if(deltaTime >= 0.05f){
        deltaTime = 0.05f;
    }
    /////
    
    //// processing Actor
    // 現時点ではハードコーディング
    // 将来的にはActorをレベルファイルからロードする機能をつける。
    mUpdatingActor = true;
    for(auto actor : mActors){
        actor->Update(deltaTime);
    }
    mUpdatingActor = false;
    
    for(auto actor : mPendingActors){
        mActors.emplace_back(actor);
    }
    std::vector<Actor*> deadActors;
    for(auto actor : mActors){
        if(actor->GetState()==Actor::EDead){
            deadActors.emplace_back(actor);
        }
    }
    
    for(auto actor : deadActors){
        delete actor;
    }
    /////
    
    // Audio
    mAudioSystem->Update(deltaTime);
    
}

//// 描画
void Game::Output(){
    // OpenGL rendering
    glClearColor(0.1f, 0.8f, 0.2f, 1.0f); // Color Setting
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color

    
    
    // Draw mesh components
    // Enable depth buffering/disable alpha blend
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    // Set the mesh shader active
    mMeshShader->SetActive();
    // ビュー行列のアップデートは描画時のみ
    mMeshShader->SetMatrixUniform("uViewProj", mView * mProj);
    // 光の情報もアップデート
    SetLightUniforms(mMeshShader);
    
    // 各メッシュコンポーネントの描画
    // シェーダーの切り替えを少なくするため、使うシェーダーごとにメッシュコンポーネントを分ける。
    for (auto mc : mMeshComps)
    {
        mc->Draw(mMeshShader);
    }
    
    mBasicMeshShader->SetActive();
    mBasicMeshShader->SetMatrixUniform("uViewProj", mView * mProj);
    SetLightUniforms(mBasicMeshShader);
    for (auto mc : mBasicMeshComps){
        mc->Draw(mBasicMeshShader);
    }
    
    //
    glDisable(GL_DEPTH_TEST);
    // スプライトの描画ではアルファブレンドを有効に
    // 仕組み　：　アルファ値が小さいほどカラーバッファに書きこまれづらくなる。0なら全く書きこまれないため透明になる。
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // スプライト用のシェーダとVAOをアクティブに
    // (これらは１ゲーム１セット？)
    mSpriteShader->SetActive();
    mSpriteVertices->SetActive();
    for (auto sc : mSpriteComps)
    {
        sc->Draw(mSpriteShader);
    }
    
    SDL_GL_SwapWindow(mWindow); // exchange front and back buffer
}
////

// 
// 渡されたファイル名のテクスチャがロードずみか確認、なかったらロードしてmTexturesに格納
Texture* Game::LoadTexture(const std::string& filename){
    Texture* text = nullptr;
    auto itr = mTextures.find(filename);
    if(itr != mTextures.end()){
        text = itr->second;
    } else {
        text = new Texture();
        if(text->Load(filename)){
            mTextures.emplace(filename,text);
        } else {
            delete text;
            text = nullptr;
        }
    }
    return text;
}
////

//// 渡されたファイル名のメッシュがロード済みか確認、なかったらロードしてmMeshesに格納
Mesh* Game::LoadMesh(const std::string &filename){
    Mesh* mesh = nullptr;
    // 渡されたファイル名のメッシュがあるか確認
    auto itr = mMeshes.find(filename);
    if(itr != mMeshes.end()){
        mesh = itr->second;
    } else { // なかったら新しく作る。
        mesh = new Mesh();
        if(mesh->Load(filename, this)){
            mMeshes.emplace(filename,mesh);
        } else { // ロードに失敗
            delete mesh;
            mesh = nullptr;
        }
    }
    return mesh;
}
////

//// 物体のゲームへの登録
void Game::AddActor(Actor *actor){
    if(mUpdatingActor){
        mPendingActors.emplace_back(actor);
    } else {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor *actor){
    auto itr = std::find(mActors.begin(),mActors.end(),actor);
    if(itr != mActors.end()){
        mActors.erase(itr);
    }
    
    itr = std::find(mPendingActors.begin(),mPendingActors.end(),actor);
    if(itr != mPendingActors.end()){
        mPendingActors.erase(itr);
    }
}
////

//// スプライトの追加・削除
void Game::AddSprite(SpriteComponent* sprite){
    int order = sprite->GetDrawOrder();
    auto itr = mSpriteComps.begin();
    for(; itr!=mSpriteComps.end();++itr){
        if((*itr)->GetDrawOrder() > order){
            break;
        }
    }
    mSpriteComps.insert(itr, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite){
    auto itr = std::find(mSpriteComps.begin(),mSpriteComps.end(),sprite);
    if(itr != mSpriteComps.end()){
        mSpriteComps.erase(itr);
    }
}
////

//// メッシュの追加・削除
void Game::AddMesh(MeshComponent* mesh){
    // 3Dは描画順序関係ないので(depth buffer)そのままpush
    mMeshComps.emplace_back(mesh);
}

void Game::RemoveMesh(MeshComponent* mesh){
    auto itr = std::find(mMeshComps.begin(),mMeshComps.end(),mesh);
    if(itr != mMeshComps.end()){ // 指定したメッシュが存在したら削除
        mMeshComps.erase(itr);
    }
}

void Game::AddBasicMesh(MeshComponent* mesh){
    // 3Dは描画順序関係ないので(depth buffer)そのままpush
    mBasicMeshComps.emplace_back(mesh);
}

void Game::RemoveBasicMesh(MeshComponent* mesh){
    auto itr = std::find(mBasicMeshComps.begin(),mBasicMeshComps.end(),mesh);
    if(itr != mBasicMeshComps.end()){ // 指定したメッシュが存在したら削除
        mBasicMeshComps.erase(itr);
    }
}
////

//// Enemy
void Game::AddEnemy(Enemy* enemy){
    mEnemies.emplace_back(enemy);
}

void Game::RemoveEnemy(Enemy* enemy){
    auto itr = std::find(mEnemies.begin(),mEnemies.end(),enemy);
    if(itr != mEnemies.end()){
        mEnemies.erase(itr);
    }
}

//// OpenGL

// SpriteVertices
// 頂点データをシェーダに渡す。
void Game::CreateSpriteVertices(){
    // 1~3番目　オブジェクト空間の座標
    // 4,5番目　UV座標
    // 一つの頂点に2つの頂点属性を持つ？
    // UVへのオフセット　ー　sizeof(float)*3
    // ストライド　ー　sizeof(float) * 5
    float vertices[] = {
        -0.5f,  0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, // top left
        0.5f,  0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, // top right
        0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, // bottom right
        -0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f  // bottom left
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    mSpriteVertices = new VertexArray(vertices, 4, indices, 6);
}

// シェーダープログラムを作成してゲームに追加 -> シェーダをGPUに読み出し？
bool Game::LoadShaders(){
    //// スプライトシェーダーの読み込み
    mSpriteShader = new Shader();
    if(!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag")){
        return false;
    }
    mSpriteShader->SetActive();
    Matrix4 simpleView = Matrix4::CreateSimpleViewProj(1024.0f, 768.0f);
    mSpriteShader->SetMatrixUniform("uViewProj", simpleView);
    ////
    
    //// メッシュシェーダーの読み込み
    mMeshShader = new Shader();
    if(!mMeshShader->Load("Shaders/Phong.vert", "Shaders/Phong.frag")){
        return false;
    }
    mMeshShader->SetActive();
    
    mBasicMeshShader = new Shader();
    if(!mBasicMeshShader->Load("Shaders/BasicMesh.vert", "Shaders/BasicMesh.frag")){
        return false;
    }
    mBasicMeshShader->SetActive();
    // ビュー射影行列をuniformに登録　ー　現時点ではこれはゲーム中に変わるものではないため一回のみ設定。
    // ビュー行列　：　上方向が+z, +x向きに初期化
    mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
    // 射影行列　：　透視投影を使用、水平視野、画面の幅、高さ、near, farを設定。
    mProj = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), 1024.0f, 768.0f, 25.0f, 10000.0f);
    mMeshShader->SetMatrixUniform("uViewProj", mView * mProj);
    ////
    
    return true;
}

// Phongシェーダーのuniformに光源の設定をsetting
void Game::SetLightUniforms(Shader* shader){
    // ビュー行列を反転してカメラの位置を求める。
    Matrix4 invView = mView;
    invView.Invert();
    shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
    // 環境光
    shader->SetVectorUniform("uAmbientLight", mAmbientLight);
    // 平行光源
    shader->SetVectorUniform("uDirLight.mDirection", mDirLight.mDirection); // 方向
    shader->SetVectorUniform("uDirLight.mDiffuseColor", mDirLight.mDiffuseColor); // 拡散反射
    shader->SetVectorUniform("uDirLight.mSpecColor", mDirLight.mSpecColor); // 鏡面反射
}

// Audio 押されたボタンで再生を変える。
void Game::HandleKeyPress(int key){
    switch (key)
    {
        case '-':
        {
            // Reduce master volume
            float volume = mAudioSystem->GetBusVolume("bus:/");
            volume = Math::Max(0.0f, volume - 0.1f);
            mAudioSystem->SetBusVolume("bus:/", volume);
            break;
        }
        case '=':
        {
            // Increase master volume
            float volume = mAudioSystem->GetBusVolume("bus:/");
            volume = Math::Min(1.0f, volume + 0.1f);
            mAudioSystem->SetBusVolume("bus:/", volume);
            break;
        }
        case 'e':
            // Play explosion
            mAudioSystem->PlayEvent("event:/Explosion2D");
            break;
        case 'm':
            // Toggle music pause state
            mMusicEvent.SetPaused(!mMusicEvent.GetPaused());
            break;
        case 'r':
            // Stop or start reverb snapshot
            if (!mReverbSnap.IsValid())
            {
                mReverbSnap = mAudioSystem->PlayEvent("snapshot:/WithReverb");
            }
            else
            {
                mReverbSnap.Stop();
            }
            break;
//        case '1':
//            // Set default footstep surface
//            mCameraActor->SetFootstepSurface(0.0f);
//            break;
//        case '2':
//            // Set grass footstep surface
//            mCameraActor->SetFootstepSurface(0.5f);
//            break;
        default:
            break;
    }
}
