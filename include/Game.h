#pragma once
#include <irrlicht/irrlicht.h>
#include <vector>
#include <math.h>
#include "IGameObject.h"
#include "EventReceiver.h"
#include "config.h"
#include "Bullet.h"
#include "Player.h"

namespace InGameStates{
    enum States{
        LOAD,
        PLAY,
        PAUSE,
        QUIT
    };
}

class GameScreen: public IGameObject, public IEventReceiver{
private:
    EventReceiver* eventmgr;
    IrrlichtDevice* device;
    InGameStates::States mGameState;
    virtual bool OnEvent(const SEvent& event);
    Bullet* m_bullet;
    Player* m_player;
public:
    GameScreen(irr::IrrlichtDevice* device);
    virtual ~GameScreen();

    virtual void update(irr::u32 DeltaTime, GameStates::GAME_STATE& gs);
    virtual void drawAll();
};
