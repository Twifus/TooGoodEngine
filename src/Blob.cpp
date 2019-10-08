#include <Blob.hpp>

Blob::Blob(Vector3 pos) {
    blobElements[0] = Particle((double) BLOB_COMPONENT_MASS, pos);
    Vector3 spawnPos;

    double x = PIXEL_UNIT;
    double y = 0.0;

    (void) x;
    (void) y;

    for (int i = 1; i < 7; ++i) {
        //init particles
    }
}

void Blob::addForces() {

}