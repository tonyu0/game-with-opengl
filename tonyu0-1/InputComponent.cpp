//
//  InputComponent.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/22.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "InputComponent.hpp"
#include "Bullet.hpp"
#include <SDL/SDL.h>

InputComponent::InputComponent(Actor* owner) : MoveComponent(owner){
    
}

void InputComponent::ProcessKeyboard(const uint8_t *state){
    float forwardSpeed = 0.0f;
    float angularSpeed = 0.0f;
    if(state[SDL_SCANCODE_UP]){
        forwardSpeed += 200;
    }
    if(state[SDL_SCANCODE_DOWN]){
        forwardSpeed -= 200;
    }
    if(state[SDL_SCANCODE_LEFT]){
        angularSpeed -= 10;
    }
    if(state[SDL_SCANCODE_RIGHT]){
        angularSpeed += 10;
    }
    
    SetForwardSpeed(forwardSpeed);
    SetAngularSpeed(angularSpeed);
}
