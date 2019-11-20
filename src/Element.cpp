#include <Element.hpp>

Element::Element(BoxRigidBody& boxRigidBody, float size) : cube(size, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag"), rigidBody(boxRigidBody) {

}

void Element::display(glm::mat4& projection, glm::mat4& modelview) {
    cube.prepare(rigidBody.GetPosition(), rigidBody.GetOrientation());
    cube.display(projection, modelview);
}
