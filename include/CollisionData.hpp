#pragma once
#include <vector>
#include "Contacts/Contact.hpp"
#include "Primitive.hpp"

namespace TooGoodEngine {
	class CollisionData
	{
	private:
		std::vector<Contacts::Contact> contacts;									//Vector of all contacts
		int maxContact;																//Value of the maximum of elements in the vector 

	public:
		CollisionData(int nbContact);												//CollisionData constructor
		~CollisionData();															//CollisionData destructor

		void GenerateContacts(const Primitive& prim1, const Primitive& prim2);		//Method which add a Contact in the contacts Vector in the case of a collision
		std::vector<Contacts::Contact>& GetContacts();
	};
}