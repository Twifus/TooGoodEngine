#include <OpenGLScene.hpp>
#include <Box3DModel.hpp>

using namespace TooGoodEngine;

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

    auto* rigidBody = new BoxRigidBody(10, 2,2,2);
    Vector3 dim = Vector3(2.,3.,5.);
    Graph3DModel *boxModel = new Box3DModel(dim);
    Element testElement = Element(rigidBody, *boxModel);
    scene.addElement(testElement);

    scene.mainLoop();

	free(rigidBody);

    return EXIT_SUCCESS;
}