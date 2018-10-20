#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#pragma once
#include <irrlicht/irrlicht.h>
#include <string>
#include "IGameObject.h"
#include "Bullet.h"
#include "TextureLoader.h"

class LevelLoader {
private:
    irr::scene::ISceneManager* m_sceneManager;
    Bullet* m_bullet;
    std::string m_levelName;
    void load();
public:
    LevelLoader(irr::scene::ISceneManager* sceneManager, Bullet* bullet, std::string levelName);
    virtual ~LevelLoader();
};


#endif // LEVELLOADER_H
