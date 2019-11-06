#include "Blob.hpp"
#include "Forces/Registery.hpp"
#include "Forces/Generators/Spring.hpp"
#include <algorithm>
#include <iostream>

#define INTER_PARTICLE_DIST (1.25)
#define ELASTICITY 150
#define ELEMENT_RADIUS (0.5)
#define MOVE_FORCE 100

Blob::Blob(Vector3 pos) : assembled(true) {
    // Create all particles of the blob
    // Center
    blobElements[0] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS, pos);
    // First Circle
    blobElements[1]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + INTER_PARTICLE_DIST,
                    pos.y,
                    0.));
    blobElements[2]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + (INTER_PARTICLE_DIST / 2.0),
                    pos.y + INTER_PARTICLE_DIST,
                    0.));
    blobElements[3]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x - (INTER_PARTICLE_DIST / 2.0),
                    pos.y + INTER_PARTICLE_DIST,
                    0.));
    blobElements[4]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x - INTER_PARTICLE_DIST,
                    pos.y,
                    0.));
    blobElements[5]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x - (INTER_PARTICLE_DIST / 2.0),
                    pos.y - INTER_PARTICLE_DIST,
                    0.));
    blobElements[6]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + (INTER_PARTICLE_DIST / 2.0),
                    pos.y - INTER_PARTICLE_DIST,
                    0.));
    // Second Circle
    blobElements[7]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + (INTER_PARTICLE_DIST * 2.0),
                    pos.y,
                    0.));
    blobElements[8]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + (INTER_PARTICLE_DIST * 3.0 / 2.0),
                    pos.y + INTER_PARTICLE_DIST,
                    0.));
    blobElements[9]  = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + INTER_PARTICLE_DIST,
                    pos.y + (INTER_PARTICLE_DIST * 2.0),
                    0.));
    blobElements[10] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x,
                    pos.y + (INTER_PARTICLE_DIST * 2.0),
                    0.));
    blobElements[11] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x - INTER_PARTICLE_DIST,
                    pos.y + (INTER_PARTICLE_DIST * 2.0),
                    0.));
    blobElements[12] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x - (INTER_PARTICLE_DIST * 3.0 / 2.0),
                    pos.y + INTER_PARTICLE_DIST,
                    0.));
    blobElements[13] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x - (INTER_PARTICLE_DIST * 2.0),
                    pos.y,
                    0.));
    blobElements[14] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x - (INTER_PARTICLE_DIST * 3.0 / 2.0),
                    pos.y - INTER_PARTICLE_DIST,
                    0.));
    blobElements[15] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x  - INTER_PARTICLE_DIST,
                    pos.y - (INTER_PARTICLE_DIST * 2.0),
                    0.));
    blobElements[16] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x,
                    pos.y - (INTER_PARTICLE_DIST * 2.0),
                    0.));
    blobElements[17] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + INTER_PARTICLE_DIST,
                    pos.y - (INTER_PARTICLE_DIST * 2.0),
                    0.));
    blobElements[18] = Particle(BLOB_COMPONENT_MASS, ELEMENT_RADIUS,
            Vector3(pos.x + (INTER_PARTICLE_DIST * 3.0 / 2.0),
                    pos.y - INTER_PARTICLE_DIST,
                    0.));

    // Create all Force generators
    initForces();
}

void Blob::initForces() {
    // 0 - 1
    internalForces.push_back(SpringSave{blobElements[0], Forces::Generators::Spring(blobElements[1], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[1], Forces::Generators::Spring(blobElements[0], ELASTICITY, INTER_PARTICLE_DIST)});
    // 0 - 2
    internalForces.push_back(SpringSave{blobElements[0], Forces::Generators::Spring(blobElements[2], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[2], Forces::Generators::Spring(blobElements[0], ELASTICITY, INTER_PARTICLE_DIST)});
    // 0 - 3
    internalForces.push_back(SpringSave{blobElements[0], Forces::Generators::Spring(blobElements[3], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[3], Forces::Generators::Spring(blobElements[0], ELASTICITY, INTER_PARTICLE_DIST)});
    // 0 - 4
    internalForces.push_back(SpringSave{blobElements[0], Forces::Generators::Spring(blobElements[4], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[4], Forces::Generators::Spring(blobElements[0], ELASTICITY, INTER_PARTICLE_DIST)});
    // 0 - 5
    internalForces.push_back(SpringSave{blobElements[0], Forces::Generators::Spring(blobElements[5], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[5], Forces::Generators::Spring(blobElements[0], ELASTICITY, INTER_PARTICLE_DIST)});
    // 0 - 6
    internalForces.push_back(SpringSave{blobElements[0], Forces::Generators::Spring(blobElements[6], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[6], Forces::Generators::Spring(blobElements[0], ELASTICITY, INTER_PARTICLE_DIST)});
    // 1 - 2
    internalForces.push_back(SpringSave{blobElements[1], Forces::Generators::Spring(blobElements[2], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[2], Forces::Generators::Spring(blobElements[1], ELASTICITY, INTER_PARTICLE_DIST)});
    // 2 - 3
    internalForces.push_back(SpringSave{blobElements[2], Forces::Generators::Spring(blobElements[3], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[3], Forces::Generators::Spring(blobElements[2], ELASTICITY, INTER_PARTICLE_DIST)});
    // 3 - 4
    internalForces.push_back(SpringSave{blobElements[3], Forces::Generators::Spring(blobElements[4], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[4], Forces::Generators::Spring(blobElements[3], ELASTICITY, INTER_PARTICLE_DIST)});
    // 4 - 5
    internalForces.push_back(SpringSave{blobElements[4], Forces::Generators::Spring(blobElements[5], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[5], Forces::Generators::Spring(blobElements[4], ELASTICITY, INTER_PARTICLE_DIST)});
    // 5 - 6
    internalForces.push_back(SpringSave{blobElements[5], Forces::Generators::Spring(blobElements[6], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[6], Forces::Generators::Spring(blobElements[5], ELASTICITY, INTER_PARTICLE_DIST)});
    // 6 - 1
    internalForces.push_back(SpringSave{blobElements[6], Forces::Generators::Spring(blobElements[1], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[1], Forces::Generators::Spring(blobElements[6], ELASTICITY, INTER_PARTICLE_DIST)});
    // 1 - 18
    internalForces.push_back(SpringSave{blobElements[1], Forces::Generators::Spring(blobElements[18], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[18], Forces::Generators::Spring(blobElements[1], ELASTICITY, INTER_PARTICLE_DIST)});
    // 1 - 7
    internalForces.push_back(SpringSave{blobElements[1], Forces::Generators::Spring(blobElements[7], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[7], Forces::Generators::Spring(blobElements[1], ELASTICITY, INTER_PARTICLE_DIST)});
    // 1 - 8
    internalForces.push_back(SpringSave{blobElements[1], Forces::Generators::Spring(blobElements[8], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[8], Forces::Generators::Spring(blobElements[1], ELASTICITY, INTER_PARTICLE_DIST)});
    // 2 - 8
    internalForces.push_back(SpringSave{blobElements[2], Forces::Generators::Spring(blobElements[8], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[8], Forces::Generators::Spring(blobElements[2], ELASTICITY, INTER_PARTICLE_DIST)});
    // 2 - 9
    internalForces.push_back(SpringSave{blobElements[2], Forces::Generators::Spring(blobElements[9], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[9], Forces::Generators::Spring(blobElements[2], ELASTICITY, INTER_PARTICLE_DIST)});
    // 2 - 10
    internalForces.push_back(SpringSave{blobElements[2], Forces::Generators::Spring(blobElements[10], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[10], Forces::Generators::Spring(blobElements[2], ELASTICITY, INTER_PARTICLE_DIST)});
    // 3 - 10
    internalForces.push_back(SpringSave{blobElements[3], Forces::Generators::Spring(blobElements[10], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[10], Forces::Generators::Spring(blobElements[3], ELASTICITY, INTER_PARTICLE_DIST)});
    // 3 - 11
    internalForces.push_back(SpringSave{blobElements[3], Forces::Generators::Spring(blobElements[11], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[11], Forces::Generators::Spring(blobElements[3], ELASTICITY, INTER_PARTICLE_DIST)});
    // 3 - 12
    internalForces.push_back(SpringSave{blobElements[3], Forces::Generators::Spring(blobElements[12], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[12], Forces::Generators::Spring(blobElements[3], ELASTICITY, INTER_PARTICLE_DIST)});
    // 4 - 12
    internalForces.push_back(SpringSave{blobElements[4], Forces::Generators::Spring(blobElements[12], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[12], Forces::Generators::Spring(blobElements[4], ELASTICITY, INTER_PARTICLE_DIST)});
    // 4 - 13
    internalForces.push_back(SpringSave{blobElements[4], Forces::Generators::Spring(blobElements[13], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[13], Forces::Generators::Spring(blobElements[4], ELASTICITY, INTER_PARTICLE_DIST)});
    // 4 - 14
    internalForces.push_back(SpringSave{blobElements[4], Forces::Generators::Spring(blobElements[14], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[14], Forces::Generators::Spring(blobElements[4], ELASTICITY, INTER_PARTICLE_DIST)});
    // 5 - 14
    internalForces.push_back(SpringSave{blobElements[5], Forces::Generators::Spring(blobElements[14], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[14], Forces::Generators::Spring(blobElements[5], ELASTICITY, INTER_PARTICLE_DIST)});
    // 5 - 15
    internalForces.push_back(SpringSave{blobElements[5], Forces::Generators::Spring(blobElements[15], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[15], Forces::Generators::Spring(blobElements[5], ELASTICITY, INTER_PARTICLE_DIST)});
    // 5 - 16
    internalForces.push_back(SpringSave{blobElements[5], Forces::Generators::Spring(blobElements[16], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[16], Forces::Generators::Spring(blobElements[5], ELASTICITY, INTER_PARTICLE_DIST)});
    // 6 - 16
    internalForces.push_back(SpringSave{blobElements[6], Forces::Generators::Spring(blobElements[16], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[16], Forces::Generators::Spring(blobElements[6], ELASTICITY, INTER_PARTICLE_DIST)});
    // 6 - 17
    internalForces.push_back(SpringSave{blobElements[6], Forces::Generators::Spring(blobElements[17], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[17], Forces::Generators::Spring(blobElements[6], ELASTICITY, INTER_PARTICLE_DIST)});
    // 6 - 18
    internalForces.push_back(SpringSave{blobElements[6], Forces::Generators::Spring(blobElements[18], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[18], Forces::Generators::Spring(blobElements[6], ELASTICITY, INTER_PARTICLE_DIST)});
    // 7 - 8
    internalForces.push_back(SpringSave{blobElements[7], Forces::Generators::Spring(blobElements[8], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[8], Forces::Generators::Spring(blobElements[7], ELASTICITY, INTER_PARTICLE_DIST)});
    // 8 - 9
    internalForces.push_back(SpringSave{blobElements[8], Forces::Generators::Spring(blobElements[9], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[9], Forces::Generators::Spring(blobElements[8], ELASTICITY, INTER_PARTICLE_DIST)});
    // 9 - 10
    internalForces.push_back(SpringSave{blobElements[9], Forces::Generators::Spring(blobElements[10], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[10], Forces::Generators::Spring(blobElements[9], ELASTICITY, INTER_PARTICLE_DIST)});
    // 10 - 11
    internalForces.push_back(SpringSave{blobElements[10], Forces::Generators::Spring(blobElements[11], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[11], Forces::Generators::Spring(blobElements[10], ELASTICITY, INTER_PARTICLE_DIST)});
    // 11 - 12
    internalForces.push_back(SpringSave{blobElements[11], Forces::Generators::Spring(blobElements[12], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[12], Forces::Generators::Spring(blobElements[11], ELASTICITY, INTER_PARTICLE_DIST)});
    // 12 - 13
    internalForces.push_back(SpringSave{blobElements[12], Forces::Generators::Spring(blobElements[13], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[13], Forces::Generators::Spring(blobElements[12], ELASTICITY, INTER_PARTICLE_DIST)});
    // 13 - 14
    internalForces.push_back(SpringSave{blobElements[13], Forces::Generators::Spring(blobElements[14], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[14], Forces::Generators::Spring(blobElements[13], ELASTICITY, INTER_PARTICLE_DIST)});
    // 14 - 15
    internalForces.push_back(SpringSave{blobElements[14], Forces::Generators::Spring(blobElements[15], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[15], Forces::Generators::Spring(blobElements[14], ELASTICITY, INTER_PARTICLE_DIST)});
    // 15 - 16
    internalForces.push_back(SpringSave{blobElements[15], Forces::Generators::Spring(blobElements[16], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[16], Forces::Generators::Spring(blobElements[15], ELASTICITY, INTER_PARTICLE_DIST)});
    // 16 - 17
    internalForces.push_back(SpringSave{blobElements[16], Forces::Generators::Spring(blobElements[17], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[17], Forces::Generators::Spring(blobElements[16], ELASTICITY, INTER_PARTICLE_DIST)});
    // 17 - 18
    internalForces.push_back(SpringSave{blobElements[17], Forces::Generators::Spring(blobElements[18], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[18], Forces::Generators::Spring(blobElements[17], ELASTICITY, INTER_PARTICLE_DIST)});
    // 18 - 7
    internalForces.push_back(SpringSave{blobElements[18], Forces::Generators::Spring(blobElements[7], ELASTICITY, INTER_PARTICLE_DIST)});
    internalForces.push_back(SpringSave{blobElements[7], Forces::Generators::Spring(blobElements[18], ELASTICITY, INTER_PARTICLE_DIST)});
}

void Blob::initDisplay(GameSDL& gameSdl) {
    for (auto& blobElement : blobElements) {
        gameSdl.CreateSprite(&blobElement, "sprites/red_circle.png");
    }
}

void Blob::addForces(Forces::Registery &registery) {
    if (assembled) {
        for (auto i = internalForces.begin(); i != internalForces.end(); ++i) {
            registery.Add(i->origin, i->forceGenerator);
        }
    }
}

void Blob::changeState() {
    assembled = !assembled;
    std::cout << "change !" << std::endl;
}

void Blob::addInternalContacts(Contacts::Resolver& resolver) {
    for (int i = 0; i < BLOB_NB_COMPONENTS; ++i)
    {
        for (auto j = i + 1; j < BLOB_NB_COMPONENTS; ++j)
        {
            if ((blobElements[i].position - blobElements[j].position).Magnitude() <= blobElements[i].GetRadius() + blobElements[j].GetRadius())
            {
				resolver.AddContact(Contacts::Contact(&(blobElements[i]), &(blobElements[j]), 0.7));
            }
        }
        if (blobElements[i].position.y <= -3.0 + ELEMENT_RADIUS)
            resolver.AddContact(Contacts::Contact(&(blobElements[i]), Vector3(0,-3,0), Vector3::up, 0.5));
    }
}

void Blob::applyForceOnAll(Forces::Registery& registery, Forces::IForceGenerator& generator) {
    for (auto &blobElement : blobElements) {
        registery.Add(blobElement, generator);
    }
}

void Blob::updatePosition(double delta) {
    for (auto &i : blobElements)
    {
        i.Update(delta);
        i.ClearForces();
    }
}

void Blob::moveImpulse(Vector3 direction, Forces::Registery &registery) {
    if (!assembled) {
        direction = direction * 0.4;
        for (int i = 0; i < BLOB_NB_COMPONENTS; ++i)
            blobElements[i].AddForce(direction * MOVE_FORCE);
    }
    else
        for (int i = 7; i < 18; i += 2)
            blobElements[i].AddForce(direction * MOVE_FORCE);
}