#include "Menu.h"
using namespace irr;

Menu::Menu(IrrlichtDevice* device){
    this->device = device;
    this->smgr = device->getSceneManager();
    this->driver = device->getVideoDriver();
    this->device->getCursorControl()->setVisible(true);
    this->login_step = LoginSteps::NONE;

    if(!smgr || !driver) return;
}

Menu::~Menu(){

}


void Menu::update(u32 DeltaTime, GameStates::GAME_STATE& gs){
}

void Menu::drawAll(){

}
