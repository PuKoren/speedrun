#include <vector>
#include <iostream>
#include <stdio.h>
#include <irrlicht/irrlicht.h>
#include "IGameObject.h"
#include "EventReceiver.h"
#include "config.h"

namespace LoginSteps{
    enum Steps{
        NONE,
        CHALLENGE,
        CREDENTIALS,
        DONE
    };
}

class Menu: public IGameObject{
private:
    scene::ISceneManager* smgr;
    irr::IrrlichtDevice* device;
    video::IVideoDriver* driver;
    scene::ICameraSceneNode* camera;
    bool isEscapeDown;
public:
    Menu(IrrlichtDevice* device);
    virtual ~Menu();
    virtual void update(irr::u32 DeltaTime, GameStates::GAME_STATE&);
    virtual void drawAll();
};
