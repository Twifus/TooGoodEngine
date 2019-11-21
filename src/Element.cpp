#include <Element.hpp>

namespace TooGoodEngine {
    Element::Element(RigidBody *rigidBody, Graph3DModel &model) : rigidBody(rigidBody), model(model) {}

    void Element::display(glm::mat4 &projection, glm::mat4 &modelview) {
        model.prepare(rigidBody->GetPosition(), rigidBody->GetOrientation());
        model.display(projection, modelview);
    }
}