#ifndef SDL_OPENGL_OPENGLSCENE_HPP
#define SDL_OPENGL_OPENGLSCENE_HPP

#include <string>

// Includes

#ifdef WIN32
#include <GL/glew.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

#include <SDL.h>
#undef main
#include <iostream>
#include <Cube.hpp>
#include <vector>

class OpenGLScene {
public:
    OpenGLScene(std::string title, int width, int height);
    ~OpenGLScene();

    bool windowInit();
    bool initGL();
    void mainLoop();

    void addElement(Cube& cube);

private:
    std::vector<Cube> elements;

    std::string windowTitle;
    int windowWidth;
    int windowHeight;

    SDL_Window* window;
    SDL_GLContext glContext;
    SDL_Event events;
};

#endif //SDL_OPENGL_OPENGLSCENE_HPP
