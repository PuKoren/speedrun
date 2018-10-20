#include "LevelLoader.h"

LevelLoader::LevelLoader(irr::scene::ISceneManager* sceneManager, Bullet* bullet, std::string levelName) {
    m_sceneManager = sceneManager;
    m_bullet = bullet;
    m_levelName = levelName;
}

void LevelLoader::load() {
    TextureLoader textureLoader(m_sceneManager->getVideoDriver());
    m_sceneManager->addSkyBoxSceneNode(textureLoader.loadTexture("skybox/bluecloud_up.jpg"),
                             textureLoader.loadTexture("skybox/bluecloud_dn.jpg"),
                             textureLoader.loadTexture("skybox/bluecloud_lf.jpg"),
                             textureLoader.loadTexture("skybox/bluecloud_rt.jpg"),
                             textureLoader.loadTexture("skybox/bluecloud_bk.jpg"),
                             textureLoader.loadTexture("skybox/bluecloud_ft.jpg"));

    //multiple cubes to test physics
    for(int i = 0; i < 100; i++){
        irr::scene::ISceneNode* tmp = m_sceneManager->addCubeSceneNode(1.0f, 0, 0, core::vector3df(0.f, rand()%40 + 20, 0.f), core::vector3df(0.f, 0.f, 0.f), core::vector3df(rand()%5+1, rand()%5+1, rand()%5+1));
        tmp->getMaterial(0).EmissiveColor = irr::video::SColor(255, 0, 0, 255);
        m_bullet->AddBox(tmp, 10.f);
    }

    //multiple balls to test physics
    for(int i = 0; i < 500; i++){
        irr::scene::ISceneNode* tmp = m_sceneManager->addSphereSceneNode(1, 8, 0, -1, core::vector3df(0.f, rand()%500, rand()%10));
        tmp->getMaterial(0).EmissiveColor = irr::video::SColor(255, 0, 0, 255);
        m_bullet->AddSphere(tmp, tmp->getTransformedBoundingBox().getExtent().X/2, 10.f);
    }

    //this is the central floor
    irr::scene::ISceneNode* tmp = m_sceneManager->addCubeSceneNode(1.0f, 0, 0, core::vector3df(0.f, -100.f, 0.f), core::vector3df(0.f, 0.f, 0.f), core::vector3df(1000.f, 10.f, 1000.f));
    tmp->setVisible(true);
    tmp->getMaterial(0).EmissiveColor = irr::video::SColor(0, 0, 255, 0);
    btRigidBody* rbody = m_bullet->AddBox(tmp, 0.f, true);
    rbody->setFriction(1.f);

    //add light
    irr::scene::ILightSceneNode*  pLight = m_sceneManager->addLightSceneNode();
    irr::video::SLight & l = pLight->getLightData();
    l.DiffuseColor = irr::video::SColor(255, 255, 0, 0);
    l.CastShadows = true;
    l.Attenuation = core::vector3df(10.f, 1.f, 1.f);
    l.Type = irr::video::ELT_DIRECTIONAL;
    pLight->setPosition(core::vector3df(-10.f, 0.f, -100.f));

    return;
}
