//
//  AudioComponent.hpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/04/01.
//  Copyright © 2019 Nakagawa. All rights reserved.
//
#pragma once
#ifndef AudioComponent_hpp
#define AudioComponent_hpp

#include "Component.hpp"
#include "SoundEvent.hpp"
#include <vector>

#endif /* AudioComponent_hpp */

// アクターにサウンドイベントをくっつける
// アクターの移動時にサウンドイベントの3D属性を更新できる。
class AudioComponent : public Component {
public:
    AudioComponent(class Actor* owner, int updateOrder = 200);
    ~AudioComponent();
    
    void Update(float deltaTime) override;
    void OnUpdateWorldTransform() override;
    
    SoundEvent PlayEvent(const std::string& name);
    void StopAllEvents();
private:
    std::vector<SoundEvent> mEvent2D;
    std::vector<SoundEvent> mEvent3D;
};
