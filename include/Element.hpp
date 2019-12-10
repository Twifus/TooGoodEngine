#ifndef TOOGOODENGINE_ELEMENT_HPP
#define TOOGOODENGINE_ELEMENT_HPP

#include "BoxRigidBody.hpp"
#include "Graph3DModel.hpp"

namespace TooGoodEngine {

	class Element {
	public:
		Element(RigidBody* rigidBody, Graph3DModel& model);

		RigidBody* rigidBody;
		Graph3DModel& model;

		void display(glm::mat4& projection, glm::mat4& modelview);
	};
}

#endif //TOOGOODENGINE_ELEMENT_HPP
