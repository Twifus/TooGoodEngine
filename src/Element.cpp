#include <Element.hpp>

Element::Element(float mass, float size, Vector3 position) : cube(size, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag")/*, rigidBody(mass, size, size, size)*/ {

}

void Element::display(glm::mat4& projection, glm::mat4& modelview) {
    cube.display(projection, modelview);
}
