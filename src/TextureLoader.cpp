#include "TextureLoader.h"

TextureLoader::TextureLoader(video::IVideoDriver *driver, std::string basePath) {
    this->driver = driver;
    this->basePath = basePath;
}

TextureLoader::~TextureLoader() {

}

video::ITexture* TextureLoader::loadTexture(std::string name) {
    return this->driver->getTexture((this->basePath + name).c_str());
}
