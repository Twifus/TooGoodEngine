#include "CollisionData.hpp"
#include "BoxPrimitive.hpp"

namespace TooGoodEngine {
	CollisionData::CollisionData(int nbContact) : maxContact(nbContact) {}
	CollisionData::~CollisionData() {}

	void CollisionData::GenerateContacts(const Primitive& prim1, const Primitive& prim2)
	{
		auto res = prim1.ResolveCollision(prim2);
		contacts.insert(contacts.end(), res.begin(), res.end());
	}
}