//
// Created by bbabu on 9/25/2019.
//

#ifndef SDL_OPENGL_TEXTURE_HPP
#define SDL_OPENGL_TEXTURE_HPP

#include <string>
#include <GL/glew.h>

#include <SDL_image.h>
#include <SDL_surface.h>
#include <iostream>

class Texture {

private:
    GLuint id;
    std::string imageSrc;

public:
    Texture(std::string imageFile);
    ~Texture();

    GLuint getID() const;
    void setImageSrc(const std::string &imageFile);

    bool load();
};

#endif //SDL_OPENGL_TEXTURE_HPP
