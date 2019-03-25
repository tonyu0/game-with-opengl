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

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <string>
#include <vector>
#include <unordered_map>

#endif /* Game_hpp */

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
    
    //Texture
    SDL_Texture* LoadTexture(const std::string filename);
    
private:
    void Input();
    void Update();
    void Output();
    

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    std::unordered_map<std::string, SDL_Texture*> mTextures;
    bool mIsRunning;
    int mTicksCount;
    // 物体管理
    class Player* mPlayer;
    
    // Actor manegement
    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;
    bool mUpdatingActor;
    
    std::vector<class SpriteComponent*> mSprites;
    std::vector<class Enemy*> mEnemies;
    
    // OpenGL
    SDL_GLContext mContext;
};
