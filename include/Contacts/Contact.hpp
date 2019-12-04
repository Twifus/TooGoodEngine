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
			double interpenetration;
			Vector3 contactNormal;
			Vector3 contactPoint;
			

		public:
			Contact(Vector3 contactPoint, Vector3 normal, double penetration);
			
	}
}