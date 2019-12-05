#include <list>
#include <random>

#include "BSPTree.hpp"

using namespace TooGoodEngine;
using namespace std;


struct Object;

static const int MAX_LEAF_DATASIZE = 6;

struct Plan {
    Vector3 position;
    Vector3 normal;
};

static const Plan planNull{Vector3::zero, Vector3::zero};

struct BSPNode {
    BSPNode* back;
    BSPNode* front;
    Plan plan;
    list<Object> data;
};


// ------------------------------------------------------------------------ //
// Some useless func that could be written directly to prevent func call

// Point distance to a plan (+ - dist)
inline double distanceToPlan(const Vector3& point, const Plan& plan) {
    return (point - plan.position).Dot(plan.normal);
}

// Test if we are at end of tree
inline bool isLeaf(const BSPNode *node) {
    return (node->back == nullptr && node->front == nullptr);
}

// Return position of the object in 3D space /!\ TODO : changer en fonction de comment est l'objet
inline Vector3 objectPosition(const Object &o) {
    return Vector3::zero;
}
// Return the size of the object  /!\ TODO : changer en fonction de comment est l'objet
inline double objectRadius(const Object &o) {
    return 1;
}

// ------------------------------------------------------------------------ //

// Constructor
BSP::BSP(Vector3 pos_start) : distribution(-10,10) {
    // create node and insert in root
    root.emplace_back(nullptr, nullptr, Plan{pos_start, Vector3::zero}, list<Object>());
}

// Split a node in two and create his children (then reallocate data)
void BSP::SplitNode(BSPNode &node) {
    // select plan (and so set up the plan for splitting data)
    node.plan.position = objectPosition(node.data.front());
    node.plan.normal   = Vector3(distribution(generator), distribution(generator), distribution(generator)).Normalized();
    // create leaf nodes and add to root
    BSPNode leaf1{nullptr, nullptr, planNull, list<Object>()};
    BSPNode leaf2{nullptr, nullptr, planNull, list<Object>()};
    root.push_back(leaf1);
    node.front = &root.back(); // To ensure we wont target a copie that doesn't exist anymore
    root.push_back(leaf2);
    node.back = &root.back();  // Same
    // insert data into it
    list<Object> result_list;
    for(const Object &obj : node.data) {
        double dist = distanceToPlan(objectPosition(obj), node.plan);
        if (dist > objectRadius(obj)) {
            if (dist > 0)
                node.front->data.push_back(obj);
            else
                node.back->data.push_back(obj);
        }
        else {
            result_list.push_back(obj);
        }
    }
    node.data = result_list;
}

// Add an object to the tree
void BSP::AddObject(const Object &object) { // pointer func compare +1 -1 0 (front back middle ?)
    // Iteration on nodes (plan back / front)
    BSPNode *node = &root.front();
    bool stop = false;
    while (!isLeaf(node)) {
        double dist = distanceToPlan(objectPosition(object), node->plan);
        if (dist < objectRadius(object))
            break;
        if (dist > 0)
            node = node->front;
        else
            node = node->back;
    }
    node->data.push_back(object);
    // Is it necessary to split node in two ? (too much objects, might be good to precise)
    if (node->data.size() > MAX_LEAF_DATASIZE && isLeaf(node))
        SplitNode(*node);
}


void checkFonc(Object &a, Object &b)
{
    // do stuffs (could be in parameter of Evaluate as well for maximum gasm)
}

// Iterate on a node
void BSP::EvaluateNode(BSPNode &node) { // ((void*) func(void)) pointer ?
    // Calling checkFonc on data
    if (node.data.size() > 1) {
        for(auto it1=node.data.begin(); it1 != node.data.end(); ++it1) {
            for (auto it2=it1; it2 != node.data.end(); ++it2) {
                checkFonc(*it1, *it2);
            }
        }
    }
    // recursion on children
    if (!isLeaf(&node)){
        EvaluateNode(*(node.back));
        EvaluateNode(*(node.front));
    }
}

// Parse BSP data and call func on every objects in the same area
void BSP::Evaluate() {
    EvaluateNode(root.front());
}

