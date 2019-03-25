//
//  InputComponent.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/03/22.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#ifndef InputComponent_hpp
#define InputComponent_hpp

#include <stdio.h>
#include "MoveComponent.hpp"

#endif /* InputComponent_hpp */

// プレイヤーなどのActorはこのComponentを追加。
class InputComponent : public MoveComponent{
public:
    InputComponent(class Actor* owner);
};
