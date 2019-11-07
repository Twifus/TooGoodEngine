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
				double vAB = (-particleA->GetVelocity()).Dot(contactNormal);
				Vector3 impulsion = -(1 + restitution) * particleA->GetMass() * vAB * contactNormal;
				particleA->AddImpulsion(-impulsion);
			}
			else
			{
				double vAB = ApproachVelocity();
				Vector3 impulsion = -(1 + restitution) * vAB / (particleA->GetInverseMass() + particleB->GetInverseMass()) * contactNormal;
				particleA->AddImpulsion(-impulsion);
				particleB->AddImpulsion(impulsion);
			}
		}


		void Contact::Resolve()
		{
			ResolvePenetration();
			ResolveVelocity();
		}
	} // namespace Contacts
} // namespace TooGoodEngine
