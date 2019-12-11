#pragma once
#include <list>

#include "Contacts/BoundingSphere.hpp"
#include "Primitive.hpp"


namespace TooGoodEngine {
    class GameObject {
    public:
        std::list<Primitive*> prime;
        Contacts::BoundingSphere sphere;
        RigidBody* rigidBody = nullptr;
        GameObject() : sphere(Vector3::zero, 0) {} 
        GameObject(std::list<Primitive*>& primeList) :
            prime(primeList), sphere(Vector3::zero, 0) {}
        GameObject(std::list<Primitive*>& primeList, float boundingRadius, RigidBody* rigidBody) :
            prime(primeList), rigidBody(rigidBody), sphere(Vector3::zero, 0) {
            sphere = Contacts::BoundingSphere(rigidBody->GetPosition(), boundingRadius);
        }
    };

}