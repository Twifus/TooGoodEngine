#pragma once
#include "Contacts/Contact.hpp"
#include "RigidBody.hpp"
#include <vector>

#define PRIMITIVE(_UID)											\
	static const uint32_t primitiveUID = _UID;					\
	virtual uint32_t GetUID() const { return primitiveUID; }

namespace TooGoodEngine {
	class Primitive
	{
	public:
		PRIMITIVE('NONE')

	protected:
		Primitive() = default;
	
	public:
		virtual std::vector<Contacts::Contact> ResolveCollision(const Primitive& other) const = 0;
	};
}
