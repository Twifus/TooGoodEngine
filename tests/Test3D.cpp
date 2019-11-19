#include <OpenGLScene.hpp>

int main()
{
    OpenGLScene scene = OpenGLScene("3DTest", 800, 600);

    bool res = scene.windowInit();
    if (!res) {
        std::cerr << "Error creating window" << std::endl;
        return EXIT_FAILURE;
    }

    res = scene.initGL();
    if (!res) {
        std::cerr << "Error initializing GL" << std::endl;
        return EXIT_FAILURE;
    }

    Element testElement = Element(10,1, Vector3());
    scene.addElement(testElement);

    scene.mainLoop();

    return EXIT_SUCCESS;
}