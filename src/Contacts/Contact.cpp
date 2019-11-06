#include "Contacts/Contact.hpp"

namespace TooGoodEngine
{
	namespace Contacts
	{
		Contact::Contact(Particle* a, Particle* b, double r)
		{
			isBplane = 0;
			restitution = r;
			particleA = a;
			particleB = b;
			contactNormal = (a->position - b->position).Normalized();
			interpenetration = b->GetRadius() + a->GetRadius() - (b->position - a->position).Magnitude();
		}

		Contact::Contact(Particle* a, Vector3 planPoint, Vector3 planNormal, double r)
		{
			isBplane = 1;
			restitution = r;
			particleA = a;
			particleB = nullptr;
			contactNormal = planNormal.Normalized();
			interpenetration = a->GetRadius() - (a->position - planPoint).Dot(contactNormal);
		}


		double Contact::ApproachVelocity() const
		{
			if (isBplane)
			{
				return (particleA->GetVelocity()).Dot(-contactNormal);
			}
			return (particleB->GetVelocity() - particleA->GetVelocity()).Dot(contactNormal);
		}


		void Contact::ResolvePenetration()
		{
			if (isBplane)
			{
				particleA->position += interpenetration * contactNormal;
			}
			else
			{
				double mA = particleA->GetMass();
				double mB = particleB->GetMass();
				Vector3 tmp = (1 / (mA + mB) * interpenetration) * contactNormal;
				Vector3 deltaPosA = mB * tmp;
				Vector3 deltaPosB = -mA * tmp;
				particleA->position += deltaPosA;
				particleB->position += deltaPosB;
			}

		}


		void Contact::ResolveVelocity()
		{
			if (isBplane)
			{
				double mA = particleA->GetMass();
				double uA = (particleA->GetVelocity()).Dot(-contactNormal);
				if (uA < 0) uA = -uA;
				particleA->Impulsion(restitution * mA * 2 * uA * contactNormal);
			}
			else
			{
				// Getting actual values
				double mA = particleA->GetMass();
				double mB = particleB->GetMass();
				double uA = (particleA->GetVelocity()).Dot(contactNormal);
				double uB = (particleB->GetVelocity()).Dot(contactNormal);
				// Computing new ones
				double constant = (mA * uA + mB * uB) / (mA + mB);
				double vA = restitution * mB * (uB - uA) / (mA + mB) + constant;
				double vB = restitution * mA * (uA - uB) / (mA + mB) + constant;
				// Making impulses
				particleA->Impulsion(mA * (vA - uA) * contactNormal);
				particleB->Impulsion(mB * (vB - uB) * contactNormal);
			}
		}


		void Contact::Resolve()
		{
			ResolvePenetration();
			ResolveVelocity();
		}
	} // namespace Contacts
} // namespace TooGoodEngine
