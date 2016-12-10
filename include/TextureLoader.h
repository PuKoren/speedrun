#pragma once
#include <string>
#include <irrlicht/irrlicht.h>

using namespace irr;

class TextureLoader {
private:
    std::string basePath;
    video::IVideoDriver* driver;
public:
    TextureLoader(video::IVideoDriver* driver, std::string basePath = "../assets/");
    ~TextureLoader();

    video::ITexture* loadTexture(std::string name);
};
