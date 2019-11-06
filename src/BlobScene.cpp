#include <algorithm>
#include <iostream>
#include <SDL.h>
#include <tuple>
#include <vector>

#include "Frame.hpp"
#include "Forces/Registery.hpp"
#include "GameSDL.hpp"
#include "Particle.hpp"
#include "Contacts/ParticleContact.hpp"
#include "Contacts/ParticleContactResolver.hpp"
#include "Forces/Generators/Gravity.hpp"
#include "Vector3.hpp"
#include "Sprite.hpp"
#include "Blob.hpp"

using namespace TooGoodEngine;

std::vector<Sprite> sprites;

GameSDL gameSDL = GameSDL();

bool handleMouse(SDL_Event * event, bool up, Blob& blob) {
    if ((event->type == SDL_MOUSEBUTTONDOWN) && up) {
        blob.changeState();
        up = false;
    } else if ((event->type == SDL_MOUSEBUTTONUP) && !up) {
        up = true;
    }
    return up;
}

int main (int argc, char* argv[])
{
    SDL_Event event;

    Blob blob = Blob(Vector3(0,2,0));
    blob.initDisplay(gameSDL);

    Frame f = Frame();
    ParticleContactResolver contactResolver;
    Forces::Registery registry;
    Forces::Generators::Gravity gravityGenerator;

    bool mouseUp = true;
    bool upKeyUp = true;

    ////////////////
    // EVENT LOOP //
    while (1)
    {
        // Mesure deltaTime since last frame
        f.computeDeltaFrame();

        blob.addInternalContacts(contactResolver);

        contactResolver.Resolve();
        contactResolver.Clear();

        blob.addForces(registry);
        blob.applyForceOnAll(registry, gravityGenerator);

        registry.UpdateForces(f.getDeltaFrame());
        registry.Clear();

        // Update each particle position
        blob.updatePosition(f.getDeltaFrame());

        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
            if ((event.type == SDL_MOUSEBUTTONDOWN) || (event.type == SDL_MOUSEBUTTONUP))
            {
                mouseUp = handleMouse(&event, mouseUp, blob);
            }
            if (event.type == SDL_KEYDOWN) {
                /* Check the SDLKey values and move change the coords */
                if (event.key.keysym.sym == SDLK_UP) {
                    if (upKeyUp) {
                        upKeyUp = !upKeyUp;
                        blob.moveImpulse(Vector3(0.0,1.0,0.0) * 20, registry);
                    }
                }
                if (event.key.keysym.sym == SDLK_LEFT) {
                    blob.moveImpulse(Vector3(-1.0,0.0,0.0), registry);
                }
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    blob.moveImpulse(Vector3(1.0,0.0,0.0), registry);
                }
            }
            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_UP) {
                    if (!upKeyUp) {
                        upKeyUp = !upKeyUp;
                    }
                }
            }
        }

        gameSDL.render();

        SDL_Delay(10);
    }
    // EVENT LOOP //
    ////////////////

    return EXIT_SUCCESS;
}
