#pragma once

#include <Vector3.hpp>
#include <Particle.hpp>
#include <Sprite.hpp>

#define BLOB_NB_COMPONENTS 19
#define BLOB_COMPONENT_MASS 0.2
#define BLOB_DAMPING 0.95

using namespace TooGoodEngine;

class Blob {
private:
    Particle blobElements[BLOB_NB_COMPONENTS];

public:
    explicit Blob(Vector3 pos = Vector3());
    void addForces();
    void separate();
    void assemble();
};