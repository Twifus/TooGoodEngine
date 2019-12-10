#pragma once

#include "Vector3.hpp"
#include "Particle.hpp"

namespace TooGoodEngine
{
	namespace Contacts
	{
		class Contact
		{
		private:
			double interpenetration;												//Value of the penetration of the two objects involved in the contact
			Vector3 contactNormal;													//Normal vector of the collision
			Vector3 contactPoint;													//Vector of the position of the contact point


		public:
			Contact(Vector3 contactPoint, Vector3 normal, double penetration);		//Contact constructor
		};
	}
}