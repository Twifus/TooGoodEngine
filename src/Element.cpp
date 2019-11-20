#include <Element.hpp>

Element::Element(float mass, float size, Vector3 position) : cube(size, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag"), rigidBody(mass, size, size, size) {

}

void Element::display() {

}
