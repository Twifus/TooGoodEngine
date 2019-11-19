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

    Cube cube = Cube(2.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag");

    scene.addElement(cube);

    scene.mainLoop();

    return EXIT_SUCCESS;
}