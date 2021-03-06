#include <OpenGLScene.hpp>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <Shader.hpp>
#include <utility>

namespace TooGoodEngine {

    OpenGLScene::OpenGLScene(std::string title, int width, int height) :
            windowTitle(std::move(title)),
            windowWidth(width),
            windowHeight(height),
            events(),
            window(nullptr),
            glContext(nullptr) {}

    OpenGLScene::~OpenGLScene() {
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool OpenGLScene::windowInit() {
        // SDL Initialisation

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "SDL Init Error : " << SDL_GetError() << std::endl;
            SDL_Quit();

            return false;
        }


        // OpenGL version

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


        // Double Buffer

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        // Window creation

        window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth,
                                  windowHeight,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

        if (window == nullptr) {
            std::cout << "Window creation Error : " << SDL_GetError() << std::endl;
            SDL_Quit();

            return false;
        }


        // OpenGL Context Creation

        glContext = SDL_GL_CreateContext(window);

        if (glContext == 0) {
            std::cout << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();

            return false;
        }

        return true;
    }

    bool OpenGLScene::initGL() {

#ifdef WIN32

        GLenum GLEWInit(glewInit());
        if (GLEWInit != GLEW_OK) {
            std::cout << "GLEW Init Error : " << glewGetErrorString(GLEWInit);

            SDL_GL_DeleteContext(glContext);
            SDL_DestroyWindow(window);
            SDL_Quit();

            return false;
        }

#endif

        glEnable(GL_DEPTH_TEST);

        return true;
    }

    using namespace glm;

    void OpenGLScene::mainLoop() {
        bool close(false);

        unsigned int framerate(10);
        Uint32 loopStart(0), loopEnd(0), elapsed(0);

        mat4 projection;
        mat4 modelView;

        projection = perspective(70.0, (double) windowWidth / windowHeight, 1.0, 100.0);
        modelView = mat4(1.0);

        while (!close) {
            loopStart = SDL_GetTicks();

            glClear(GL_DEPTH_BUFFER_BIT);
            glClear(GL_COLOR_BUFFER_BIT);

            SDL_PollEvent(&events);

            if (events.window.event == SDL_WINDOWEVENT_CLOSE)
                close = true;

            modelView = lookAt(glm::vec3(10, 10, 10),
                               glm::vec3(0, 0, 0),
                               glm::vec3(0, 1, 0));

            mat4 modelViewSave = modelView;

            for (Element element : elements) {
                element.display(projection, modelView);
            }

            SDL_GL_SwapWindow(window);

            loopEnd = SDL_GetTicks();
            elapsed = loopEnd - loopStart;

            if (elapsed < framerate)
                SDL_Delay(framerate - elapsed);
        }
    }

    void OpenGLScene::addElement(Element &element) {
        elements.push_back(element);
    }
}