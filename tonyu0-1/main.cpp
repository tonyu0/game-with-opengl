//
//  main.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/19.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "Game.hpp"

int main(int argc, const char * argv[]) {

    Game game;
    if(game.Initialize()){
        game.RunLoop();
    }
    
    game.ShutDown();
    

    
    return 0;
}
