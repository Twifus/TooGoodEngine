#pragma once

#include <string>

// Include Windows

#ifdef WIN32
#include <GL/glew.h>


// Include Mac

#elif __APPLE__
#include <OpenGL/gl.h>


// Include UNIX/Linux

#else
#define GL3_PROTOTYPES 1
#include <GL/gl.h>
#endif

#include <SDL.h>
#undef main
#include <iostream>
#include <vector>
#include "Element.hpp"

namespace TooGoodEngine {
    class OpenGLScene {
    public:
        OpenGLScene(std::string title, int width, int height);

        ~OpenGLScene();

        bool windowInit();

        bool initGL();

        virtual void mainLoop();

        void addElement(Element &cube);

    protected:
        std::vector<Element> elements;

        std::string windowTitle;
        int windowWidth;
        int windowHeight;

        SDL_Window *window;
        SDL_GLContext glContext;
        SDL_Event events;
    };
}
