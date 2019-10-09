#include <Blob.hpp>
#include <ForcesRegistery.hpp>
#include <SpringForceGenerator.hpp>

#define INTER_PARTICLE_DIST (PIXEL_UNIT * 30)
#define ELASTICITY 10.0
#define ELEMENT_RADIUS (PIXEL_UNIT * 13)

Blob::Blob(Vector3 pos) : assembled(true) {
    // center
    blobElements[0] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS, pos);
    // first circle
    blobElements[1]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + INTER_PARTICLE_DIST,
                    pos.y,
                    0.));
    blobElements[2]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + (INTER_PARTICLE_DIST / 2),
                    pos.y + INTER_PARTICLE_DIST,
                    0.));
    blobElements[3]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x - (INTER_PARTICLE_DIST / 2),
                    pos.y + INTER_PARTICLE_DIST,
                    0.));
    blobElements[4]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x - INTER_PARTICLE_DIST,
                    pos.y,
                    0.));
    blobElements[5]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x - (INTER_PARTICLE_DIST / 2),
                    pos.y - INTER_PARTICLE_DIST,
                    0.));
    blobElements[6]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + (INTER_PARTICLE_DIST / 2),
                    pos.y - INTER_PARTICLE_DIST,
                    0.));
    // second circle
    blobElements[7]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + (INTER_PARTICLE_DIST * 2),
                    pos.y,
                    0.));
    blobElements[8]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + (INTER_PARTICLE_DIST * 3 / 2),
                    pos.y + INTER_PARTICLE_DIST,
                    0.));
    blobElements[9]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + INTER_PARTICLE_DIST,
                    pos.y + (INTER_PARTICLE_DIST * 2),
                    0.));
    blobElements[10] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x,
                    pos.y + (INTER_PARTICLE_DIST * 2),
                    0.));
    blobElements[11] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x - INTER_PARTICLE_DIST,
                    pos.y + (INTER_PARTICLE_DIST * 2),
                    0.));
    blobElements[12] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x - (INTER_PARTICLE_DIST * 3 / 2),
                    pos.y + INTER_PARTICLE_DIST,
                    0.));
    blobElements[13] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x - (INTER_PARTICLE_DIST * 2),
                    pos.y,
                    0.));
    blobElements[14] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x - (INTER_PARTICLE_DIST * 3 / 2),
                    pos.y - INTER_PARTICLE_DIST,
                    0.));
    blobElements[15] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x  - INTER_PARTICLE_DIST,
                    pos.y - (INTER_PARTICLE_DIST * 2),
                    0.));
    blobElements[16] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x,
                    pos.y - (INTER_PARTICLE_DIST * 2),
                    0.));
    blobElements[17] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + INTER_PARTICLE_DIST,
                    pos.y - (INTER_PARTICLE_DIST * 2),
                    0.));
    blobElements[18] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + (INTER_PARTICLE_DIST * 3 / 2),
                    pos.y - INTER_PARTICLE_DIST,
                    0.));
}

void Blob::addForces(ForcesRegistery registery) {
    if (assembled) {
        // 0 - 1
        SpringForceGenerator generator = SpringForceGenerator(blobElements[1], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[0], generator);
        generator = SpringForceGenerator(blobElements[0], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[1], generator);
        // 0 - 2
        generator = SpringForceGenerator(blobElements[2], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[0], generator);
        generator = SpringForceGenerator(blobElements[0], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[2], generator);
        // 0 - 3
        generator = SpringForceGenerator(blobElements[3], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[0], generator);
        generator = SpringForceGenerator(blobElements[0], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[3], generator);
        // 0 - 4
        generator = SpringForceGenerator(blobElements[4], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[0], generator);
        generator = SpringForceGenerator(blobElements[0], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[4], generator);
        // 0 - 5
        generator = SpringForceGenerator(blobElements[5], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[0], generator);
        generator = SpringForceGenerator(blobElements[0], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[5], generator);
        // 0 - 6
        generator = SpringForceGenerator(blobElements[6], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[0], generator);
        generator = SpringForceGenerator(blobElements[0], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[6], generator);
        // 1 - 2
        generator = SpringForceGenerator(blobElements[2], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[1], generator);
        generator = SpringForceGenerator(blobElements[1], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[2], generator);
        // 2 - 3
        generator = SpringForceGenerator(blobElements[3], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[2], generator);
        generator = SpringForceGenerator(blobElements[2], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[3], generator);
        // 3 - 4
        generator = SpringForceGenerator(blobElements[4], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[3], generator);
        generator = SpringForceGenerator(blobElements[3], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[4], generator);
        // 4 - 5
        generator = SpringForceGenerator(blobElements[5], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[4], generator);
        generator = SpringForceGenerator(blobElements[4], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[5], generator);
        // 5 - 6
        generator = SpringForceGenerator(blobElements[6], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[5], generator);
        generator = SpringForceGenerator(blobElements[5], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[6], generator);
        // 6 - 1
        generator = SpringForceGenerator(blobElements[1], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[6], generator);
        generator = SpringForceGenerator(blobElements[6], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[1], generator);
        // 1 - 18
        generator = SpringForceGenerator(blobElements[1], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[18], generator);
        generator = SpringForceGenerator(blobElements[18], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[1], generator);
        // 1 - 7
        generator = SpringForceGenerator(blobElements[1], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[7], generator);
        generator = SpringForceGenerator(blobElements[7], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[1], generator);
        // 1 - 8
        generator = SpringForceGenerator(blobElements[1], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[8], generator);
        generator = SpringForceGenerator(blobElements[8], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[1], generator);
        // 2 - 8
        generator = SpringForceGenerator(blobElements[2], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[8], generator);
        generator = SpringForceGenerator(blobElements[8], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[2], generator);
        // 2 - 9
        generator = SpringForceGenerator(blobElements[2], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[9], generator);
        generator = SpringForceGenerator(blobElements[9], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[2], generator);
        // 2 - 10
        generator = SpringForceGenerator(blobElements[2], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[10], generator);
        generator = SpringForceGenerator(blobElements[10], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[2], generator);
        // 3 - 10
        generator = SpringForceGenerator(blobElements[3], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[10], generator);
        generator = SpringForceGenerator(blobElements[10], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[3], generator);
        // 3 - 11
        generator = SpringForceGenerator(blobElements[3], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[11], generator);
        generator = SpringForceGenerator(blobElements[11], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[3], generator);
        // 3 - 12
        generator = SpringForceGenerator(blobElements[3], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[12], generator);
        generator = SpringForceGenerator(blobElements[12], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[3], generator);
        // 4 - 12
        generator = SpringForceGenerator(blobElements[4], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[12], generator);
        generator = SpringForceGenerator(blobElements[12], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[4], generator);
        // 4 - 13
        generator = SpringForceGenerator(blobElements[4], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[13], generator);
        generator = SpringForceGenerator(blobElements[13], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[4], generator);
        // 4 - 14
        generator = SpringForceGenerator(blobElements[4], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[14], generator);
        generator = SpringForceGenerator(blobElements[14], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[4], generator);
        // 5 - 14
        generator = SpringForceGenerator(blobElements[5], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[14], generator);
        generator = SpringForceGenerator(blobElements[14], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[5], generator);
        // 5 - 15
        generator = SpringForceGenerator(blobElements[5], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[15], generator);
        generator = SpringForceGenerator(blobElements[15], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[5], generator);
        // 5 - 16
        generator = SpringForceGenerator(blobElements[5], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[16], generator);
        generator = SpringForceGenerator(blobElements[16], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[5], generator);
        // 6 - 16
        generator = SpringForceGenerator(blobElements[6], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[16], generator);
        generator = SpringForceGenerator(blobElements[16], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[6], generator);
        // 6 - 17
        generator = SpringForceGenerator(blobElements[6], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[17], generator);
        generator = SpringForceGenerator(blobElements[17], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[6], generator);
        // 6 - 18
        generator = SpringForceGenerator(blobElements[6], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[18], generator);
        generator = SpringForceGenerator(blobElements[18], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[6], generator);
        // 7 - 8
        generator = SpringForceGenerator(blobElements[7], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[8], generator);
        generator = SpringForceGenerator(blobElements[8], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[7], generator);
        // 8 - 9
        generator = SpringForceGenerator(blobElements[8], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[9], generator);
        generator = SpringForceGenerator(blobElements[9], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[8], generator);
        // 9 - 10
        generator = SpringForceGenerator(blobElements[9], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[10], generator);
        generator = SpringForceGenerator(blobElements[10], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[9], generator);
        // 10 - 11
        generator = SpringForceGenerator(blobElements[10], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[11], generator);
        generator = SpringForceGenerator(blobElements[11], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[10], generator);
        // 11 - 12
        generator = SpringForceGenerator(blobElements[11], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[12], generator);
        generator = SpringForceGenerator(blobElements[12], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[11], generator);
        // 12 - 13
        generator = SpringForceGenerator(blobElements[12], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[13], generator);
        generator = SpringForceGenerator(blobElements[13], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[12], generator);
        // 13 - 14
        generator = SpringForceGenerator(blobElements[13], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[14], generator);
        generator = SpringForceGenerator(blobElements[14], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[13], generator);
        // 14 - 15
        generator = SpringForceGenerator(blobElements[14], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[15], generator);
        generator = SpringForceGenerator(blobElements[15], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[14], generator);
        // 15 - 16
        generator = SpringForceGenerator(blobElements[15], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[16], generator);
        generator = SpringForceGenerator(blobElements[16], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[15], generator);
        // 16 - 17
        generator = SpringForceGenerator(blobElements[16], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[17], generator);
        generator = SpringForceGenerator(blobElements[17], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[16], generator);
        // 17 - 18
        generator = SpringForceGenerator(blobElements[17], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[18], generator);
        generator = SpringForceGenerator(blobElements[18], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[17], generator);
        // 18 - 7
        generator = SpringForceGenerator(blobElements[18], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[7], generator);
        generator = SpringForceGenerator(blobElements[7], ELASTICITY, INTER_PARTICLE_DIST);
        registery.Add(blobElements[18], generator);
    }
}

void Blob::assemble() {
    assembled = true;
}

void Blob::separate() {
    assembled = false;
}