#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>
#include <Box3DModel.hpp>

#include "OpenGLScene.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "Frame.hpp"
#include "BoxRigidBody.hpp"

using namespace glm;
using namespace TooGoodEngine;

std::vector<BoxRigidBody*> objects;
bool impact = false;

class CrashScene : public OpenGLScene {
public:
    CrashScene(int width, int height) : OpenGLScene("Crash Scene", width, height) {}

    void mainLoop() override {
        bool close(false);

        unsigned int framerate (10);
        Uint32 loopStart(0), loopEnd(0), elapsed(0);

        mat4 projection;
        mat4 modelView;

        projection = perspective(70.0, (double) windowWidth / windowHeight, 1.0, 100.0);

        double time = 0;
        double display_time = 0;

        Frame f = Frame();

        while (!close) {
            // Physics
            f.computeDeltaFrame();

            AddForces(f.getDeltaFrame());

            // Maj de tous les objets
            for (auto i : objects)
            {
                i->Update(f.getDeltaFrame());
                i->ClearAccumulation();
            }

            // Affichage toute les 1/2 seconde
            /*display_time += f.getDeltaFrame();
            if (display_time >= 0.1)
            {
                std::cout << "=====" << std::endl;
                Display(objects[0], "Car 1");
                std::cout << "---" << std::endl;
                Display(objects[1], "Car 2");
                std::cout << "----" << std::endl;
                Display(objects[2], "Flying cube");
                std::cout << std::endl;
                display_time = 0;
            }*/

            // display
            loopStart = SDL_GetTicks();

            glClear(GL_DEPTH_BUFFER_BIT);
            glClear(GL_COLOR_BUFFER_BIT);

            SDL_PollEvent(&events);

            if(events.window.event == SDL_WINDOWEVENT_CLOSE)
                close = true;

            modelView = lookAt(glm::vec3(2,10,4),
                               glm::vec3(5,0,0),
                               glm::vec3(0,1,0));

            mat4 modelViewSave = modelView;

            for (Element element : elements) {
                modelView = modelViewSave;

                modelViewSave = modelView;

                element.display(projection, modelView);

                modelView = modelViewSave;
            }

            SDL_GL_SwapWindow(window);

            loopEnd = SDL_GetTicks();
            elapsed = loopEnd - loopStart;

            if (elapsed < framerate)
                SDL_Delay(framerate - elapsed);
        }
    }

    void AddForces(double time)
    {
        // Force vers l'avant (en coordonnées locales) appliquée au centre de masse
        objects[0]->AddForceAtBodyPoint(Vector3(15 * time, 0, 0), Vector3::zero);

        // Force vers l'avant (en coordonnées locales) appliquée au centre de masse
        objects[1]->AddForceAtBodyPoint(Vector3(15 * time, 0, 0), Vector3::zero);

        if (!impact && std::abs(objects[0]->GetPosition().x - objects[1]->GetPosition().x) < 2)
        {
            std::cout << "==================\n===== IMPACT =====\n==================" << std::endl;
            impact = true;
            objects[1]->AddForceAtBodyPoint(Vector3(-10000 * time, 0, 0), Vector3(2, 1, 1));
        }

        // Forces opposées en coordonnées locales pour faire tourner l'objet sur lui même sur place
		objects[2]->AddForceAtBodyPoint(Vector3(0, 10 * time, 0), Vector3(1, 0, 0));
		objects[2]->AddForceAtBodyPoint(Vector3(0, -10 * time, 0), Vector3(-1, 0, 0));
    }

// Affichage des objets
    void Display(const RigidBody &body, const char* name)
    {
        Vector3 corner_pos = body.BodyToWorld(Vector3(1,1,1));
        std::cout << "[ " << name << " ]" << std::endl;
        std::cout << "center" << body.GetPosition() << "\t\tcorner" << corner_pos << std::endl;
        std::cout << "vitesse lin." << body.GetVelocity() << "\t\tvitesse ang." << body.GetAngularVelocity() << std::endl;
    }
};

// Crée les boites de test
void CreateBody(CrashScene& scene) {
    // Voiture 1 vers la droite (sur l'axe x)
    auto *car1 = new BoxRigidBody(10, 3, 2, 2);
    car1->SetPosition(- Vector3::forward / 2);
    objects.push_back(car1);

    Vector3 dimensions = Vector3(3,2,2);
    Vector3 color = Vector3(1,0,0);
    auto *car1Model = new Box3DModel(dimensions, color);

    Element carElement1 = Element(objects[0], *car1Model);
    scene.addElement(carElement1);

    // Voiture 2 vers la gauche (sur l'axe x)
    auto* car2 = new BoxRigidBody(10, 3, 2, 2);
    car2->SetPosition(Vector3::right * 10 + Vector3::forward / 2);
    car2->SetOrientation(Quaternion::AxisAngle(Vector3::up, M_PI)); // 180 degree autour de y
    objects.push_back(car2);

    color = Vector3(0,1,0);
    auto *car2Model = new Box3DModel(dimensions, color);
    Element carElement2 = Element(objects[1], *car2Model);
    scene.addElement(carElement2);

    // Cube en l'air (en haut à droite dans le plan xy)
    auto* fly = new BoxRigidBody(2, 1, 1, 1);
    fly->SetPosition(5 * Vector3::right - 5 *  Vector3::forward);
    objects.push_back(fly);

    dimensions = Vector3(2,2,2);
    color = Vector3(1,1,1);
    auto *flyingModel = new Box3DModel(dimensions, color);
    Element flyingElement = Element(objects[2], *flyingModel);
    scene.addElement(flyingElement);
}

// Main
int main ()
{
    CrashScene scene = CrashScene(800, 600);

    bool res = scene.windowInit();
    if (!res)
        return -1;
    res = scene.initGL();
    if (!res)
        return -1;

    CreateBody(scene);

    // Boucle de jeu
    scene.mainLoop();

	for (BoxRigidBody* rb : objects)
		free(rb);
    
    return 0;
}