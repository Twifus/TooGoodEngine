#include "CollisionData.hpp"

namespace TooGoodEngine {
	CollisionData::CollisionData(int nbContact) : maxContact(nbContact) {}
	CollisionData::~CollisionData() {}

	void CollisionData::GenerateContacts(const Primitive& prim1, const Primitive& prim2) {
		double distance = (prim1.boundingSphere.center - prim2.boundingSphere.center).Magnitude();
		double radiuses = prim1.boundingSphere.radius + prim2.boundingSphere.radius;

		//If collision
		if (distance < radiuses) {
			Vector3 normal = (prim1.boundingSphere.center - prim2.boundingSphere.center).Normalized();		//Normal vector of the collision
			Vector3 contactPoint = (prim1.boundingSphere.center + prim1.boundingSphere.radius * normal);	//Vector of the position of the contact point
			double penetration = radiuses - distance;														//Value of the penetration of the two objects involved in the collision

			Contacts::Contact newContact = Contacts::Contact(contactPoint, normal, penetration);
			contacts.push_back(newContact);
		}
	}
}