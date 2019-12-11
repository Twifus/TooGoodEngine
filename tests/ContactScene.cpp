#include <GameObject.hpp>
#include <OpenGLScene.hpp>
#include <BoxRigidBody.hpp>
#include <Box3DModel.hpp>
#include <BoxPrimitive.hpp>
#include <PlanPrimitive.hpp>
#include <Contacts/BoundingSphere.hpp>
#include <Element.hpp>
#include <BSPTree.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <Frame.hpp>
#include <CollisionData.hpp>

#include <vector>

using namespace TooGoodEngine;
using namespace glm;

std::vector<BoxRigidBody*> objects;

/**
 * @class ContactScene
 * A scene class made to handle GameObject
 */
class ContactScene : public OpenGLScene {
private:
    std::vector<GameObject*> gameObjects;
	std::vector<Contacts::Contact> contacts;

public:
    ContactScene() : OpenGLScene("Contact Example", 1366, 768) {}

    void addGameObject(GameObject* gameObject) {
        gameObjects.push_back(gameObject);
    }

    void AddForces(double time) {
		objects[0]->AddForceAtBodyPoint(Vector3(2, 0.5, 0), Vector3(0, 0.5, 0));
    }


    void mainLoop() override {
        bool close(false);
		bool pause(false);
        BSPTree contactTree;

        unsigned int framerate(10);
        Uint32 loopStart(0), loopEnd(0), elapsed(0);

        mat4 projection;
        mat4 modelView;

        double time = 0;
        double display_time = 0;

        Frame f = Frame();
		AddForces(f.getDeltaFrame());

        projection = perspective(70.0, (double) windowWidth / windowHeight, 1.0, 100.0);
        modelView = mat4(1.0);

        while (!close) {
			if (!pause) {
				contacts = std::vector<Contacts::Contact>();

				loopStart = SDL_GetTicks();

				contactTree = BSPTree();

				f.computeDeltaFrame();

				for (GameObject* gameObject : gameObjects) {
					gameObject->updateSphere();
					contactTree.AddGameObject(*gameObject);
				}

				contactTree.Evaluate();

				contacts = contactTree.collision.GetContacts();

				if (contacts.size() != 0) {
					for (auto& contact : contacts) {
						contact.print();
					}
					
					pause = true;
				}

				for (auto i : objects)
				{
					i->Update(0.5);
					i->ClearAccumulation();
				}

				glClear(GL_DEPTH_BUFFER_BIT);
				glClear(GL_COLOR_BUFFER_BIT);

				modelView = lookAt(glm::vec3(9, 9, 9),
					glm::vec3(10, 0, 0),
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
			SDL_PollEvent(&events);

			if (events.window.event == SDL_WINDOWEVENT_CLOSE)
				close = true;
        }
    }
};

int main()
{
    ContactScene scene = ContactScene();

    scene.windowInit();
    scene.initGL();

    // Cube creation
    Vector3 size(2,2,2);
    Vector3 color(1,0,0);
    Box3DModel cubeModel = Box3DModel(size, color);
    BoxRigidBody cubeRigidBody = BoxRigidBody(10, 2, 2, 2);
	objects.push_back(&cubeRigidBody);
    Element cubeElement = Element(&cubeRigidBody, cubeModel);
    scene.addElement(cubeElement);
    objects.push_back(&cubeRigidBody);

    size = Vector3(1,1,1);
    BoxPrimitive cubePrimitive = BoxPrimitive(cubeRigidBody, size);
    auto cubePrimitives = std::list<Primitive*>();
    cubePrimitives.push_back(&cubePrimitive);
    GameObject cubeGO = GameObject(cubePrimitives, 1.8f, &cubeRigidBody);
    scene.addGameObject(&cubeGO);

    // Planes creation
    // Plane x = -10
    size = Vector3(0.1,100,100);
    color = Vector3(0,1,0);
    Box3DModel nXPlaneModel = Box3DModel(size, color);
    BoxRigidBody nXPlanRB = BoxRigidBody(1000, 0.1, 0.1, 0.1);
    nXPlanRB.SetPosition(Vector3(-10, 0, 0));
    Element nXPlanElement = Element(&nXPlanRB, nXPlaneModel);
    scene.addElement(nXPlanElement);
    PlanPrimitive nXPlanPrimitive = PlanPrimitive(Vector3(1, 0, 0), 10);
    auto nXPlanPrimitives = std::list<Primitive*>();
    nXPlanPrimitives.push_back(&nXPlanPrimitive);
    GameObject nXPlanGO = GameObject(nXPlanPrimitives, 1, &nXPlanRB);
    scene.addGameObject(&nXPlanGO);

    // Plane x = 10
    Box3DModel XPlaneModel = Box3DModel(size, color);
    BoxRigidBody XPlanRB = BoxRigidBody(1000, 0.1, 0.1, 0.1);
    XPlanRB.SetPosition(Vector3(10, 0, 0));
    Element XPlanElement = Element(&XPlanRB, XPlaneModel);
    scene.addElement(XPlanElement);
    PlanPrimitive XPlanPrimitive = PlanPrimitive(Vector3(-1, 0, 0), 10);
    auto XPlanPrimitives = std::list<Primitive*>();
    XPlanPrimitives.push_back(&XPlanPrimitive);
    GameObject XPlanGO = GameObject(XPlanPrimitives, 1, &XPlanRB);
    scene.addGameObject(&XPlanGO);

    // Plane y = -10
    size = Vector3(100, 0.1, 100);
    color = Vector3(0,0,1);
    Box3DModel nYPlaneModel = Box3DModel(size, color);
    BoxRigidBody nYPlanRB = BoxRigidBody(1000, 0.1, 0.1, 0.1);
    nYPlanRB.SetPosition(Vector3(0, -10, 0));
    Element nYPlanElement = Element(&nYPlanRB, nYPlaneModel);
    scene.addElement(nYPlanElement);
    PlanPrimitive nYPlanPrimitive = PlanPrimitive(Vector3(0, 1, 0), 10);
    auto nYPlanPrimitives = std::list<Primitive*>();
    nYPlanPrimitives.push_back(&nYPlanPrimitive);
    GameObject nYPlanGO = GameObject(nYPlanPrimitives, 1, &nYPlanRB);
    scene.addGameObject(&nYPlanGO);

    Box3DModel YPlaneModel = Box3DModel(size, color);
    BoxRigidBody YPlanRB = BoxRigidBody(1000, 0.1, 0.1, 0.1);
    YPlanRB.SetPosition(Vector3(0, -10, 0));
    Element YPlanElement = Element(&YPlanRB, YPlaneModel);
    scene.addElement(YPlanElement);
    PlanPrimitive YPlanPrimitive = PlanPrimitive(Vector3(0, -1, 0), 10);
    auto YPlanPrimitives = std::list<Primitive*>();
    YPlanPrimitives.push_back(&YPlanPrimitive);
    GameObject YPlanGO = GameObject(YPlanPrimitives, 1, &YPlanRB);
    scene.addGameObject(&YPlanGO);

    size = Vector3(100,100,0.1);
    color = Vector3(0,1,1);
    Box3DModel nZPlaneModel = Box3DModel(size, color);
    BoxRigidBody nZPlanRB = BoxRigidBody(1000, 0.1, 0.1, 0.1);
    nZPlanRB.SetPosition(Vector3(0, -10, 0));
    Element nZPlanElement = Element(&nZPlanRB, nZPlaneModel);
    scene.addElement(nZPlanElement);
    PlanPrimitive nZPlanPrimitive = PlanPrimitive(Vector3(0, 0, 1), 10);
    auto nZPlanPrimitives = std::list<Primitive*>();
    nZPlanPrimitives.push_back(&nZPlanPrimitive);
    GameObject nZPlanGO = GameObject(nZPlanPrimitives, 1, &nZPlanRB);
    scene.addGameObject(&nZPlanGO);

    Box3DModel ZPlaneModel = Box3DModel(size, color);
    BoxRigidBody ZPlanRB = BoxRigidBody(1000, 0.1, 0.1, 0.1);
    ZPlanRB.SetPosition(Vector3(0, -10, 0));
    Element ZPlanElement = Element(&ZPlanRB, ZPlaneModel);
    scene.addElement(ZPlanElement);
    PlanPrimitive ZPlanPrimitive = PlanPrimitive(Vector3(1, 0, -1), 10);
    auto ZPlanPrimitives = std::list<Primitive*>();
    ZPlanPrimitives.push_back(&ZPlanPrimitive);
    GameObject ZPlanGO = GameObject(ZPlanPrimitives, 1, &ZPlanRB);
    scene.addGameObject(&nXPlanGO);

    scene.mainLoop();
}