#include "Game.h"

GameScreen::GameScreen(IrrlichtDevice *device){
    this->device = device;
    this->device = device;
    this->device->getCursorControl()->setVisible(true);

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
    m_player = new Player(smgr, m_bullet, device->getEventReceiver());
    for(int i = 0; i < 100; i++){
        irr::scene::ISceneNode* tmp = smgr->addCubeSceneNode(1.0f, 0, 0, core::vector3df(rand()%40, rand()%40 + 20, 40.f));
        tmp->getMaterial(0).EmissiveColor = irr::video::SColor(255, 128, 50, 30);
        m_bullet->AddBox(tmp, 1.f)->setLinearFactor(btVector3(1, 1, 1));
    }

    irr::scene::ISceneNode* tmp = smgr->addCubeSceneNode(100.0f, 0, 0, core::vector3df(0.f, -100.f, 0.f));
    tmp->getMaterial(0).EmissiveColor = irr::video::SColor(255, 128, 50, 30);
    m_bullet->AddBox(tmp, 0.f, true);

//    WorldGenerator gen(smgr, device->getVideoDriver(), m_bullet);
//    gen.LoadLevel(0, 0);
//    gen.LoadLevel(1, 0);
//    gen.LoadLevel(2, 0);
}

GameScreen::~GameScreen(){
    delete this->m_player;
    delete this->m_bullet;
}

bool GameScreen::OnEvent(const SEvent &event){
    return false;
}

void GameScreen::update(u32 DeltaTime, GameStates::GAME_STATE &gs){
    this->m_player->update(DeltaTime, gs);
    this->m_bullet->UpdatePhysics(DeltaTime);
}

void GameScreen::drawAll(){

}
