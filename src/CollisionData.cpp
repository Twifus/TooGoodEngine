#include "CollisionData.hpp"

namespace TooGoodEngine {
	CollisionData::CollisionData(int nbContact) : maxContact(nbContact) {}
	CollisionData::~CollisionData() {}

	void CollisionData::GenerateContacts(const Primitive& prim1, const Primitive& prim2) {
		double distance = (prim1.boundingSphere.center - prim2.boundingSphere.center).Magnitude();
		double radiuses = prim1.boundingSphere.radius + prim2.boundingSphere.radius;

		if (distance < radiuses) {
			Vector3 normal = (prim1.boundingSphere.center - prim2.boundingSphere.center).Normalized();
			Vector3 contactPoint = (prim1.boundingSphere.center + prim1.boundingSphere.radius * normal);
			double penetration = radiuses - distance;
			Contacts::Contact newContact = Contacts::Contact(contactPoint, normal, penetration);
			contacts.push_back(newContact);
		}
	}
}