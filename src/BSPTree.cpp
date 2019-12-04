#include "BSPTree.hpp"

struct Object;

struct Plan {
    Vector3 position;
    Vector3 direction;
};

struct BSPNode {
    BSPNode *back;
    BSPNode *front;
    Plan plan;
    Object* data;
};

