#ifndef TOOGOODENGINE_ELEMENT_HPP
#define TOOGOODENGINE_ELEMENT_HPP

#include <BoxRigidBody.hpp>
#include <Cube.hpp>

namespace TooGoodEngine {

    class Element {
    public:
        Element(BoxRigidBody* boxRigidBody, float size);

        BoxRigidBody* rigidBody;
        Cube cube;

        void display(glm::mat4& projection, glm::mat4& modelview);
    };
}

#endif //TOOGOODENGINE_ELEMENT_HPP
