//
//  AudioSystem.cpp
//  tonyu0-1
//
//  Created by Nakagawa on 2019/04/01.
//  Copyright © 2019 Nakagawa. All rights reserved.
//

#include "AudioSystem.hpp"
#include <SDL/SDL_log.h>
#include <fmod_studio.hpp>
#include <fmod_errors.h>

// イベントインスタンスのID管理用
unsigned int AudioSystem::sID = 0;

AudioSystem::AudioSystem(Game* game) : mGame(game), mSystem(nullptr), mLowLevelSystem(nullptr) {
    
}

AudioSystem::~AudioSystem(){
    
}

bool AudioSystem::Initialize(){
    FMOD::Debug_Initialize(
        FMOD_DEBUG_LEVEL_ERROR, // エラーでだけログをとる(設定しないとエラーメッセージが多い)
        FMOD_DEBUG_MODE_TTY // stdoutに出力
                           );
    
    // FMOD Studioシステムのインスタンスを作る。
    FMOD_RESULT result;
    result = FMOD::Studio::System::create(&mSystem);
    if(result != FMOD_OK){
        SDL_Log("FMODシステムの作成に失敗！ : %s", FMOD_ErrorString(result));
        return false;
    }
    result = mSystem->initialize(512, // 最大同時発音数
                                 FMOD_STUDIO_INIT_NORMAL, // デフォルト(FMOD STUDIO API)
                                 FMOD_INIT_CHANNEL_LOWPASS, // ローパスフィルタを有効化(FMOD Low Level API)
                                 nullptr); // 追加のドライバ
    // Low Level Systemのポインタを取得
    mSystem->getLowLevelSystem(&mLowLevelSystem);
    
    // 他のバンクファイルを読むのに必要な、2つのマスターバンクファイル(stringsが先)
    LoadBank("Assets/Master Bank.strings.bank"); // 人間が読める文字でFMOD Studioのデータにアクセスできるようになる
    LoadBank("Assets/Master Bank.bank");
    
    return true;
}

void AudioSystem::Update(float deltaTime){
    // 終了したイベントインスタンスを探す
    std::vector<unsigned int> done; // 終了状態のイベントのIDを格納
    
    for(auto itr : mEventInstances){ // 全てのインスタンスの状態を確認
        FMOD::Studio::EventInstance* e = itr.second;
        FMOD_STUDIO_PLAYBACK_STATE state;
        e->getPlaybackState(&state); // 状態取得
        if(state==FMOD_STUDIO_PLAYBACK_STOPPED){
            e->release();
            done.emplace_back(itr.first);
        }
    }
    
    for(auto id : done){
        mEventInstances.erase(id); // イベントを消したくない場合は、イベントの状態をpauseにする。
    }
    // 3Dオーディオなどの再計算
    mSystem->update();
}

void AudioSystem::ShutDown(){
    mSystem->release();
}

void AudioSystem::LoadBank(const std::string& name){
    if(mBanks.find(name) != mBanks.end()){
        return;
    }
    
    // バンクをロード
    FMOD::Studio::Bank* bank = nullptr;
    FMOD_RESULT result = mSystem->loadBankFile(name.c_str(),
                                               FMOD_STUDIO_LOAD_BANK_NORMAL, // 通常の読み込み
                                               &bank);
    //
    const int maxPathLength = 512;
    if(result == FMOD_OK){
        mBanks.emplace(name, bank);
        // ストリーミング以外のさんプルデータを全てロード?
        bank->loadSampleData();
        int numEvents = 0;
        bank->getEventCount(&numEvents);
        if(numEvents > 0){
            // バンクにあるイベント記述子のリストを取得
            std::vector<FMOD::Studio::EventDescription* > events(numEvents);
            bank->getEventList(events.data(), numEvents, &numEvents);
            char eventName[maxPathLength];
            for(int i=0;i<numEvents;++i){
                FMOD::Studio::EventDescription* e = events[i];
                // このイベントのぱパスを設定して
                e->getPath(eventName, maxPathLength, nullptr);
                // イベント連想配列に追加
                mEvents.emplace(eventName, e);
            }
        }
    }
}

void AudioSystem::UnloadBank(const std::string &name){
    auto itr = mBanks.find(name);
    if(itr == mBanks.end()){ // 存在したら消す
        return;
    }
    FMOD::Studio::Bank* bank = itr->second;
    int numEvents = 0;
    
    // イベントが存在したら、全てのイベントを削除
    bank->getEventCount(&numEvents);
    if(numEvents > 0){
        std::vector<FMOD::Studio::EventDescription* > events(numEvents);
        bank->getEventList(events.data(), numEvents, &numEvents);
        char eventName[512];
        for(int i=0;i<numEvents;++i){
            FMOD::Studio::EventDescription* e = events[i];
            e->getPath(eventName, 512, nullptr);
            auto eitr = mEvents.find(eventName);
            if(eitr != mEvents.end()){
                mEvents.erase(eitr);
            }
        }
    }
    
    bank->unloadSampleData();
    bank->unload();
    mBanks.erase(itr);
}


SoundEvent AudioSystem::PlayEvent(const std::string &name){
    unsigned int id = 0;
    auto itr = mEvents.find(name);
    if(itr != mEvents.end()){
        // EventInstanceを作成
        FMOD::Studio::EventInstance* e = nullptr;
        itr->second->createInstance(&e);
        if(e) { // インスタンスが作成できたら
            e->start(); // イヴェントの開始
            ++sID;
            id = sID;
            mEventInstances.emplace(id, e);
            // e->release();
            // イベントのインスタンスは停止時に破棄される。　→ ループしないイベントは自動的にとまる。
            // SoundEventクラスの実装により、e->release()は呼ばれなくなった。
            // そのかわり、Updateで不要になったイベントインスタンスをクリーン
        }
    }
    // 現状、ループするイベントが止まらない。
    // イベントパラメーター（ボリュームなど）を変更できない。
    // しかしイベントインスタンスのポインタをそのまま返すのはあれなので、イベントを管理するクラスをベット作る。
    return SoundEvent(this, id);
}

FMOD::Studio::EventInstance* AudioSystem::GetEventInstance(unsigned int id){
    auto itr = mEventInstances.find(id);
    if(itr != mEventInstances.end()){
        return itr->second;
    }
    return nullptr;
}

namespace {
    FMOD_VECTOR VecToFMOD(const Vector3& in){
        // このゲームの座標系(+xが前、+yが右、+zが上)からFMOD(+zが前、+xが右、+yが上)に変換
        FMOD_VECTOR v;
        v.x = in.y;
        v.y = in.z;
        v.z = in.x;
        return v;
    }
}

// ビュー行列を受け取って、リスナーの位置と、ビューからの前方ベクトルと上向きベクトルを設定。
void AudioSystem::SetListener(const Matrix4& view){
    // カメラからリスナーをセット
    // ビュー行列の逆行列を考えることでカメラの位置、前方、上を取得。
    Matrix4 invView = view;
    invView.Invert();
    
    // リスナーを準備
    FMOD_3D_ATTRIBUTES listener;
    listener.position = VecToFMOD(invView.GetTranslation());
    // FMODでは前方がz軸
    listener.forward = VecToFMOD(invView.GetZAxis());
    // FMODではupがy軸
    listener.up = VecToFMOD(invView.GetYAxis());
    
    //速度は０にセット(ドップラー効果を使うときは修正)
    listener.velocity = {0.0f,0.0f,0.0f};
    //FMODに送る
    mSystem->setListenerAttributes(0, &listener);
}

// バスを制御する関数
float AudioSystem::GetBusVolume(const std::string &name) const {
    float ret = 0.0f;
    const auto itr = mBuses.find(name);
    if(itr != mBuses.end()){
        itr->second->getVolume(&ret);
    }
    return ret;
}

bool AudioSystem::GetBusPaused(const std::string &name) const {
    bool ret = false;
    const auto itr = mBuses.find(name);
    if(itr != mBuses.end()){
        itr->second->getPaused(&ret);
    }
    return ret;
}

void AudioSystem::SetBusVolume(const std::string &name, float volume){
    auto itr = mBuses.find(name);
    if(itr != mBuses.end()){
        itr->second->setVolume(volume);
    }
}

void AudioSystem::SetBusPaused(const std::string &name, bool pause){
    auto itr = mBuses.find(name);
    if(itr != mBuses.end()){
        itr->second->setPaused(pause);
    }
}
