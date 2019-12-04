#include "Contacts/Contact.hpp"

namespace TooGoodEngine
{
	namespace Contacts
	{
		Contact::Contact(Vector3 point, Vector3 normal, double penetration) : contactPoint(point), contactNormal(normal), interpenetration(penetration) {}

	} // namespace Contacts
} // namespace TooGoodEngine
