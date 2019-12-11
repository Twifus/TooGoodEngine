#include "../include/BSPTree.hpp"
#include "../include/GameObject.hpp"
#include "../include/CollisionData.hpp"


using namespace TooGoodEngine;


int main() {
    std::list<Primitive*> emptyPrime;
    Contacts::BoundingSphere sph1(Vector3(0,0,0), 5),
        sph2(Vector3(10,10,10), 5),
        sph3(Vector3(-5,-5, 0), 3),
        sph4(Vector3(11,10,10), 0.5);

    GameObject liste[4];
    liste[0] = GameObject(emptyPrime, sph1);
    liste[1] = GameObject(emptyPrime, sph2);
    liste[2] = GameObject(emptyPrime, sph3);
    liste[3] = GameObject(emptyPrime, sph4);

    CollisionData collision = CollisionData(5);
    BSPTree testTree(collision);

    for(auto go : liste) {
        testTree.AddGameObject(go);
    }

    testTree.Evaluate();

    return 0;
}