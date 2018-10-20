#include "Game.h"

GameScreen::GameScreen(IrrlichtDevice *device){
    this->device = device;
    this->device = device;
    this->device->getCursorControl()->setVisible(false);

    //irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    //video::IVideoDriver* driver = device->getVideoDriver();
    eventmgr = (EventReceiver*)device->getEventReceiver();

    /*
    irr::scene::ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator(camera->getPosition(), 200.f);
    camera->addAnimator(anim);
    anim->drop();
    */

    this->m_bullet = new Bullet();

    //player
    m_player = new Player(smgr, m_bullet, device->getEventReceiver());

    m_levelLoader = new LevelLoader(smgr, this->m_bullet, "01");
}

GameScreen::~GameScreen(){
    delete this->m_levelLoader;
    delete this->m_player;
    delete this->m_bullet;
}

bool GameScreen::OnEvent(const SEvent &event){
    return false;
}

void GameScreen::update(u32 DeltaTime, GameStates::GAME_STATE &gs){
    this->m_bullet->UpdatePhysics(DeltaTime);
    this->m_player->update(DeltaTime, gs);

    if(((EventReceiver*)device->getEventReceiver())->IsKeyDown(KEY_ESCAPE)) {
        gs = GameStates::MENU;
    }
}

void GameScreen::drawAll(){

}
