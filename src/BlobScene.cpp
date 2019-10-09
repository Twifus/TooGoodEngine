#include <algorithm>
#include <iostream>
#include <SDL.h>
#include <tuple>
#include <vector>

#include "Frame.hpp"
#include "ForcesRegistery.hpp"
#include "GameSDL.hpp"
#include "Particle.hpp"
#include "ParticleContact.hpp"
#include "ParticleContactResolver.hpp"
#include "ParticleForceGenerator.hpp"
#include "GravityForceGenerator.hpp"
#include "Vector3.hpp"
#include "Sprite.hpp"
#include <Blob.hpp>

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
    ForcesRegistery registry;
    GravityForceGenerator gravityGenerator;

    bool up = true;

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
                up = handleMouse(&event, up, blob);
            }
        }

        gameSDL.render();
    }
    // EVENT LOOP //
    ////////////////

    return EXIT_SUCCESS;
}
