#pragma once

#include <vector>
#include "Vector3.hpp"
#include "Particle.hpp"
#include "Sprite.hpp"
#include "Forces/Registery.hpp"
#include "Forces/Generators/Spring.hpp"
#include "Contacts/Resolver.hpp"
#include "GameSDL.hpp"

#define BLOB_NB_COMPONENTS 19
#define BLOB_COMPONENT_MASS 1

using namespace TooGoodEngine;

/**
 * A blob composed of 19 particles disposed in 2 hexagons
 */
class Blob {
private:
    // Structure of the particles in the blob

    //       11 -  10 -  9
    //      /  \  /  \  /  \
    //    12 -  3  -  2  -  8
    //   /  \  /  \  /  \  /  \
    // 13 -  4  -  0  -  1  -  7
    //   \  /  \  /  \  /  \  /
    //    14 -  5  -  6  -  18
    //      \  /  \  /  \  /
    //       15 -  16 -  17

    Particle blobElements[BLOB_NB_COMPONENTS];  /// Table of the blob particles
    bool assembled;                             /// Boolean stating whether the spring forces in the blob are active

    /**
     * Structure used to save a one-way link between two particles
     */
    struct SpringSave {
        Particle& origin;                       /// Particle to which the spring is fixed
        Forces::Generators::Spring forceGenerator;    /// Force generator of the spring
    };

    std::vector<SpringSave> internalForces;     /// Vector to save all internal interactions due to springs

    void initForces();                          /// Setup of all the internal forces

public:
    /**
     * Creates a 19 particles Blob at a given position
     * @param pos The starting position of the central point
     */
    explicit Blob(Vector3 pos = Vector3());

    void initDisplay(GameSDL& gameSdl);

    /**
     * Add all internal forces to the registery if they are active
     * @param registery the force registery of the game
     */
    void addForces(Forces::Registery& registery);

    /**
     * Switch the activation of the internal springs
     */
    void changeState();

    void addInternalContacts(Contacts::Resolver& resolver);

    void applyForceOnAll(Forces::Registery& registery, Forces::IForceGenerator& generator);

    void updatePosition(double delta);

    void moveImpulse(Vector3 direction, Forces::Registery& registery);
};