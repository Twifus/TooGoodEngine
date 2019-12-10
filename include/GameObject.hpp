#pragma once
#include <list>

#include "Contacts/BoundingSphere.hpp"
#include "Primitive.hpp"


namespace TooGoodEngine {
    class GameObject {
    public:
        std::list<Primitive> prime;
        Contacts::BoundingSphere sphere;
        GameObject() : sphere(Vector3::zero, 0) {} 
        GameObject(std::list<Primitive> primeList, Contacts::BoundingSphere sphere) :
            prime(primeList), sphere(sphere) {}
    };

}