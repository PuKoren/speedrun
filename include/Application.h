#include <irrlicht/irrlicht.h>
#include "EventReceiver.h"
#include "Menu.h"
#include "Game.h"
#include "IGameObject.h"

class Application{
public:
    Application();
    ~Application();
    bool run();

private:
    void loadLevel();
    GameStates::GAME_STATE state;
    GameStates::GAME_STATE oldState;

    irr::IrrlichtDevice *device;
    scene::ISceneManager *smgr;
    video::IVideoDriver* driver;
    EventReceiver eventReceiver;

    IGameObject* scene;

    void updateTitle();
    int lastFPS;

    void debug();
};
