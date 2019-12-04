#pragma once
#include <vector>
#include "Contacts/Contact.hpp"
#include "Primitive.hpp"

namespace TooGoodEngine {
	class CollisionData
	{
	private:
		std::vector<Contacts::Contact> contacts;
		int maxContact;

	public:
		CollisionData(int nbContact);
		~CollisionData();

		void GenerateContacts(const Primitive& prim1, const Primitive& prim2);
	};
}