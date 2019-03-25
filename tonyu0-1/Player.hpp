//
//  Player.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/21.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Actor.hpp"

#endif /* Player_hpp */

class Player : public Actor {
public:
    Player(class Game* game);
    void UpdateActor(float deltaTime) override;
    void ProcessKeyboard(const uint8_t* state);
    
    // Getter
    float GetXSpeed() const {return mXSpeed;}
    float GetYSpeed() const {return mYSpeed;}
    
private:
    float mXSpeed;
    float mYSpeed;
};
