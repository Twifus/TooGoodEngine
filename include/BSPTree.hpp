#pragma once

#include "Vector3.hpp"

struct BSPNode;
struct Object;

class BSP {
private:
    list<BSPNode> root;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;

    void SplitNode(BSPNode &node);
    void EvaluateNode(BSPNode &node);

public:
    BSP(Vector3 pos_start);
    void AddObject(const Object &object);
    void Evaluate();
};