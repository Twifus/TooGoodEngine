#ifndef TOOGOODENGINE_ELEMENT_HPP
#define TOOGOODENGINE_ELEMENT_HPP

#include <BoxRigidBody.hpp>
#include <Cube.hpp>

namespace TooGoodEngine {

    class Element {
    public:
        Element(float mass, float size, Vector3 position);

        //BoxRigidBody rigidBody;
        Cube cube;

        void display(glm::mat4& projection, glm::mat4& modelview);
    };
}

#endif //TOOGOODENGINE_ELEMENT_HPP
