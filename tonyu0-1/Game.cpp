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
#include "BGSpriteComponent.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include <GL/glew.h>

const int thickness = 20;

Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mTicksCount(0) {
    
}

bool Game::Initialize(){
    
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
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
    
    // 第二引数　：　グラフィックスDriver マルチウインドウの時に意味がある。
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!mRenderer){
        SDL_Log("Failed to make Renderer : %s",SDL_GetError());
    }
    
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }
    
    mPlayer = new Player(this);
    mPlayer->SetPosition(Vector2(0.0f,0.0f));
    mPlayer->SetScale(1.5f);
    Actor* bg = new Actor(this);
    bg->SetPosition(Vector2(512,384));
    BGSpriteComponent* bgcomp = new BGSpriteComponent(bg);
    
    bgcomp->SetScreenSize(Vector2(1024.0f,768.0f));
    std::vector<SDL_Texture*> bgtextures = {
        LoadTexture("Farback01.png"),
        LoadTexture("Farback02.png"),
    };
    bgcomp->SetBGTextures(bgtextures);
    bgcomp->SetScrollSpeed(-100.0f);
    
    bgcomp = new BGSpriteComponent(bg,50);
    bgtextures = {
        LoadTexture("Stars.png"),
        LoadTexture("Stars.png")
    };
    bgcomp->SetScreenSize(Vector2(1024.0f, 768.0f));
    bgcomp->SetBGTextures(bgtextures);
    bgcomp->SetScrollSpeed(-200.0f);
    
    for(int i=0;i<20;++i){
        new Enemy(this);
    }
    
    
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
    // Destroy
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);
    
    // Quit IMG
    IMG_Quit();
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
            case SDL_MOUSEBUTTONDOWN:
                mIsRunning = false;
                break;
        }
    }
    
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_ESCAPE]){
        mIsRunning = false;
    }
    
    mPlayer->ProcessKeyboard(state);
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
    
}

void Game::Output(){
    // OpenGL rendering
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // Color Setting
    glClear(GL_COLOR_BUFFER_BIT); // Clear color
    
    SDL_SetRenderDrawColor(mRenderer, 255, 128, 0, 255);
    SDL_RenderClear(mRenderer); // Clear back buffer
    
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    // Drawing Upper Wall
    SDL_Rect wall{
        0,
        0,
        1024,
        thickness // 左上のx,y座標、幅、高さ
    };
    SDL_RenderFillRect(mRenderer, &wall);
    //
    
    // Drawing Lower Wall
    wall.y += 768 - thickness; // 768(画面の一番下 - 壁の厚さ)
    SDL_RenderFillRect(mRenderer, &wall);
    //
    
    
    
    for(auto sprite : mSprites){
        sprite->Draw(mRenderer);
    }
    
    SDL_GL_SwapWindow(mWindow); // exchange front and back buffer
}

SDL_Texture* Game::LoadTexture(const std::string filename){
    SDL_Texture* text = nullptr;
    auto itr = mTextures.find(filename);
    if(itr != mTextures.end()){
        text = itr->second;
    } else {
        SDL_Surface* surf = IMG_Load(filename.c_str());
        if(!surf){
            SDL_Log("Failed to load texture file %s",filename.c_str());
            return nullptr;
        }
        text = SDL_CreateTextureFromSurface(mRenderer, surf);
        SDL_FreeSurface(surf);
        if(!text){
            SDL_Log("Failed to convert surface to texture %s",filename.c_str());
            return nullptr;
        }
    }
    return text;
}

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

void Game::AddSprite(SpriteComponent* sprite){
    int order = sprite->GetDrawOrder();
    auto itr = mSprites.begin();
    for(; itr!=mSprites.end();++itr){
        if((*itr)->GetDrawOrder() > order){
            break;
        }
    }
    mSprites.insert(itr, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite){
    auto itr = std::find(mSprites.begin(),mSprites.end(),sprite);
    if(itr != mSprites.end()){
        mSprites.erase(itr);
    }
}


// Enemy
void Game::AddEnemy(Enemy* enemy){
    mEnemies.emplace_back(enemy);
}

void Game::RemoveEnemy(Enemy* enemy){
    auto itr = std::find(mEnemies.begin(),mEnemies.end(),enemy);
    if(itr != mEnemies.end()){
        mEnemies.erase(itr);
    }
}
