#pragma once

#include "RigidBody.hpp"

namespace TooGoodEngine
{
    class BoxRigidBody : public RigidBody
    {
    public:
        BoxRigidBody(double m, double l, double h, double w);
    };
}