#pragma once

#include <vector>
#include <Vector3.hpp>
#include <Particle.hpp>
#include <Sprite.hpp>
#include <SpringForceGenerator.hpp>
#include "ForcesRegistery.hpp"

#define BLOB_NB_COMPONENTS 19
#define BLOB_COMPONENT_MASS 0.2
#define BLOB_DAMPING 0.95

using namespace TooGoodEngine;

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

    Particle blobElements[BLOB_NB_COMPONENTS];
    bool assembled;

    struct SpringSave {
        Particle& origin;
        SpringForceGenerator forceGenerator;
    };

    std::vector<SpringSave> internalForces;

    void initForces();

public:
    explicit Blob(Vector3 pos = Vector3());
    void addForces(ForcesRegistery& registery);
    void changeState();
};