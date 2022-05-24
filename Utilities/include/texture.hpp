#pragma once

#include<string>

enum TextureType {
    DIFFUSE,
    SPECULAR,
    NORMAL
};

struct Texture {
    unsigned int id;
    TextureType type;
    std::string path;
};
