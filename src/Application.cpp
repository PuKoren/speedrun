#include "Application.h"

using namespace irr;

Application::Application(){

    IrrlichtDevice *nulldevice = createDevice(video::EDT_NULL);

    SIrrlichtCreationParameters params;
    params.AntiAlias = 8;
    params.Bits = 32;
    params.Vsync = false;
    params.DriverType = video::EDT_OPENGL;
    params.Stencilbuffer = true;
    params.WindowSize = nulldevice->getVideoModeList()->getDesktopResolution();
    params.EventReceiver = &eventReceiver;

    device = createDeviceEx(params);

    oldState = state = GameStates::MENU;
    scene = NULL;

    if (device){
        device->setResizable(true);
        //irrlicht managers
        driver = device->getVideoDriver();
        smgr = device->getSceneManager();
        smgr->setAmbientLight(video::SColorf(0.1f,0.1f,0.1f,1.f));
        smgr->setShadowColor(video::SColor(150,0,0,0));

        //network manager
        debug();

        loadLevel();
    }
}

Application::~Application(){
    delete scene;
    device->drop();
}

void Application::loadLevel(){
    if(scene) delete scene;

    device->getGUIEnvironment()->clear();
    device->getSceneManager()->clear();

    switch(state){
        case GameStates::MENU:
            scene = new Menu(device);
            break;
        case GameStates::EXIT:
            device->closeDevice();
            scene = NULL;
            break;
        case GameStates::INGAME:
            scene = new GameScreen(device);
            break;
        default:
            scene = new Menu(device);
            break;
    }

    oldState = state;
}

void Application::debug(){
    if (!driver->queryFeature(video::EVDF_PIXEL_SHADER_1_1) && !driver->queryFeature(video::EVDF_ARB_FRAGMENT_PROGRAM_1)){
        device->getLogger()->log("WARNING: Pixel shaders disabled because of missing driver/hardware support.");
    }

    if (!driver->queryFeature(video::EVDF_VERTEX_SHADER_1_1) && !driver->queryFeature(video::EVDF_ARB_VERTEX_PROGRAM_1)){
        device->getLogger()->log("WARNING: Vertex shaders disabled because of missing driver/hardware support.");
    }
}

void Application::updateTitle(){
    int fps = driver->getFPS();
    if (lastFPS != fps){
        core::stringw str = L"Speedrun - v0.0.1 [";
        str += driver->getName();
        str += "] FPS: ";
        str += fps;

        device->setWindowCaption(str.c_str());
        lastFPS = fps;
    }
}

bool Application::run(){
    if(!device) return false;

    ITimer* irrTimer = device->getTimer();
    u32 TimeStamp = irrTimer->getTime(), DeltaTime = 0;

    while(device->run() && driver){
        DeltaTime = irrTimer->getTime() - TimeStamp;
        TimeStamp = irrTimer->getTime();

        this->updateTitle();

        if(device->isWindowActive()){
            driver->beginScene(true, true, video::SColor(255,100,100,100));
            smgr->drawAll();
            device->getGUIEnvironment()->drawAll();
            driver->endScene();
        }

        if(scene) scene->update(DeltaTime, state);
        if(state != oldState) loadLevel();
    }

    return true;
}
