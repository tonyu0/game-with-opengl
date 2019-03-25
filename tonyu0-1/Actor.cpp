//
//  Actor.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/19.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "Game.hpp"
#include "Actor.hpp"
#include "Component.hpp"

Actor::Actor(Game* game) : mGame(game),mPosition(Vector2(0.0f,0.0f)),mScale(1.0f),mRotation(0.0f), mState(EActive) {
    mGame->AddActor(this);
}

Actor::~Actor(){
    mGame->RemoveActor(this);
    while(!mComponents.empty()){
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime){
    if(mState==EActive){
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime){
    for(auto comp : mComponents){
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime){
}

void Actor::AddComponent(Component* comp){
    int order = comp->GetUpdateOrder();
    auto itr = mComponents.begin();
    for(; itr != mComponents.end();++itr){
        if((*itr)->GetUpdateOrder() > order){
            break;
        }
    }
    mComponents.insert(itr, comp);
}

void Actor::RemoveComponent(Component* comp){
    auto itr = std::find(mComponents.begin(), mComponents.end(), comp);
    if(itr != mComponents.end()){
        mComponents.erase(itr);
    }
}

// ActorとComponent、それぞれに異なる動きを実装する為、Actorに上位クラスのProcessInputを実装。これで一括Input受付ガできるようにする。
// Component::ProcessInputはoverride可能。コンポーネントごとのInput受付。
// Actor::ActorInputはoverride可能。ActorごとのInput受付。
void Actor::ProcessInput(const int *Keystate){
    for(auto comp : mComponents){
        comp->ProcessInput(Keystate);
    }
    ActorInput(Keystate);
}

//仮想関数。ここでは書かない。
void Actor::ActorInput(const int *Keystate){
    
}
