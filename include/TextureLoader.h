#pragma once
#include <string>
#include <irrlicht/irrlicht.h>
#include <map>

using namespace irr;

class TextureLoader {
private:
    std::string basePath;
    video::IVideoDriver* driver;
    static std::map<std::string, video::ITexture*> textureCache;
public:
    TextureLoader(video::IVideoDriver* driver, std::string basePath = "../assets/");
    ~TextureLoader();

    video::ITexture* loadTexture(std::string name);
};
