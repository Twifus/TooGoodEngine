#include "Contacts/Contact.hpp"
#include <iostream>

namespace TooGoodEngine
{
	namespace Contacts
	{
		Contact::Contact(Vector3 point, Vector3 normal, double penetration) : contactPoint(point), contactNormal(normal), interpenetration(penetration) {}

		void Contact::print() {
			std::cout << "Collision:\n";
			std::cout << "\tPoint: (" << contactPoint.x << "," << contactPoint.y << "," << contactPoint.z << ")\n";
			std::cout << "\tNormal: (" << contactNormal.x << "," << contactNormal.y << "," << contactNormal.z << ")\n";
		}
	} // namespace Contacts
} // namespace TooGoodEngine
