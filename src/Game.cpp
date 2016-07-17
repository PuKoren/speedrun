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

    //multiple cubes to test physics
    for(int i = 0; i < 100; i++){
        irr::scene::ISceneNode* tmp = smgr->addCubeSceneNode(1.0f, 0, 0, core::vector3df(0.f, rand()%40 + 20, 0.f), core::vector3df(0.f, 0.f, 0.f), core::vector3df(rand()%5+1, rand()%5+1, rand()%5+1));
        tmp->getMaterial(0).EmissiveColor = irr::video::SColor(255, 0, 0, 255);
        m_bullet->AddBox(tmp, 10.f);
    }

    //multiple balls to test physics
    for(int i = 0; i < 500; i++){
        irr::scene::ISceneNode* tmp = smgr->addSphereSceneNode(1, 8, 0, -1, core::vector3df(0.f, rand()%500, rand()%10));
        tmp->getMaterial(0).EmissiveColor = irr::video::SColor(255, 0, 0, 255);
        m_bullet->AddSphere(tmp, tmp->getTransformedBoundingBox().getExtent().X/2, 10.f);
    }

    //this is the central floor
    irr::scene::ISceneNode* tmp = smgr->addCubeSceneNode(1.0f, 0, 0, core::vector3df(0.f, -100.f, 0.f), core::vector3df(0.f, 0.f, 0.f), core::vector3df(1000.f, 10.f, 1000.f));
    tmp->setVisible(true);
    tmp->getMaterial(0).EmissiveColor = irr::video::SColor(0, 0, 255, 0);
    btRigidBody* rbody = m_bullet->AddBox(tmp, 0.f, true);
    rbody->setFriction(1.f);

    //add light
    irr::scene::ILightSceneNode*  pLight = smgr->addLightSceneNode();
    irr::video::SLight & l = pLight->getLightData();
    l.DiffuseColor = irr::video::SColor(255, 255, 0, 0);
    l.CastShadows = true;
    l.Attenuation = core::vector3df(10.f, 1.f, 1.f);
    l.Type = irr::video::ELT_DIRECTIONAL;
    pLight->setPosition(core::vector3df(-10.f, 0.f, -100.f));

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
