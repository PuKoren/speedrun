#include "Menu.h"
using namespace irr;

Menu::Menu(IrrlichtDevice* device){
    this->device = device;
    this->smgr = device->getSceneManager();
    this->driver = device->getVideoDriver();
    this->device->getCursorControl()->setVisible(true);

    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    gui::IGUIStaticText* title = guienv->addStaticText(L"SPEEDRUN", core::rect<irr::s32>(0,0, driver->getScreenSize().Width, driver->getScreenSize().Height/3), false, true);
    title->setAlignment(gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT, gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT);
    title->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    title->setOverrideColor(video::SColor(255, 255, 255, 255));

    gui::IGUIStaticText* instruction = guienv->addStaticText(L"Enter to start, escape to quit", core::rect<irr::s32>(0,0, driver->getScreenSize().Width, driver->getScreenSize().Height/2), false, true);
    instruction->setAlignment(gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT, gui::EGUIA_UPPERLEFT, gui::EGUIA_LOWERRIGHT);
    instruction->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    instruction->setOverrideColor(video::SColor(255, 255, 255, 255));

    this->isEscapeDown = ((EventReceiver*)device->getEventReceiver())->IsKeyDown(KEY_ESCAPE);

    if(!smgr || !driver) return;
}

Menu::~Menu(){

}


void Menu::update(u32 DeltaTime, GameStates::GAME_STATE& gs){
    if(((EventReceiver*)device->getEventReceiver())->IsKeyDown(KEY_RETURN)){
        //start level
        gs = GameStates::INGAME;
    } else if(((EventReceiver*)device->getEventReceiver())->IsKeyDown(KEY_ESCAPE)){
        if (!this->isEscapeDown) {
            gs = GameStates::EXIT;
            this->isEscapeDown = true;
        }
    } else {
        this->isEscapeDown = false;
    }
}

void Menu::drawAll(){

}
