#include "TextureLoader.h"
std::map<std::string, video::ITexture*> TextureLoader::textureCache;

TextureLoader::TextureLoader(video::IVideoDriver *driver, std::string basePath) {
    this->driver = driver;
    this->basePath = basePath;
}

TextureLoader::~TextureLoader() {

}

video::ITexture* TextureLoader::loadTexture(std::string name) {
    std::string key = this->basePath + name;

    if (TextureLoader::textureCache[key] != NULL) {
        return TextureLoader::textureCache[key];
    }

    TextureLoader::textureCache[key] = this->driver->getTexture(key.c_str());
    return TextureLoader::textureCache[key];
}
