//
//  Player.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/21.
//  Copyright © 2019 Nakagawa. All rights reserved.
//
#pragma once
#include "Actor.hpp"
#include "CircleComponent.hpp"

/* Player_hpp */
// 上方向を+zにしたカメラの移動を表現
class Player : public Actor {
public:
    Player(class Game* game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const uint8_t *state) override;
    void ProcessKeyboard(const Uint8* state);
private:
    class CircleComponent* mCircle;
};
