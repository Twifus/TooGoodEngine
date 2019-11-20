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

    BoxRigidBody* rigidBody = new BoxRigidBody(10, 2,2,2);
    Element testElement = Element(rigidBody, 2);
    scene.addElement(testElement);

    scene.mainLoop();

	free(rigidBody);

    return EXIT_SUCCESS;
}