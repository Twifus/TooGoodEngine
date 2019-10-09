#include "ParticleContact.hpp"

namespace TooGoodEngine
{

    ParticleContact::ParticleContact(Particle* a, Particle* b, float r)
    {
        isBplane = 0;
        restitution = r;
        particleA = a;
        particleB = b;
        contactNormal = (a->position - b->position).Normalized();
        interpenetration = b->GetRadius() + a->GetRadius() - (b->position - a->position).Magnitude();
    }

    ParticleContact::ParticleContact(Particle* a, Vector3 planPoint, Vector3 planNormal, float r)
    {
        isBplane = 1;
        restitution = r;
        particleA = a;
        particleB = nullptr;
        contactNormal = planNormal.Normalized();
        interpenetration = Vector3::Dot(planPoint - a->position, contactNormal);
    }


    double ParticleContact::ApprochVelocity() const
    {
        if (isBplane)
        {
            return Vector3::Dot((particleA->GetVelocity()), -contactNormal);
        }
        return Vector3::Dot((particleB->GetVelocity() - particleA->GetVelocity()), contactNormal);
    }


    void ParticleContact::ResolvePenetration()
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


    void ParticleContact::ResolveVelocity()
    {
        if (isBplane)
        {
            double mA = particleA->GetMass();
            double uA = Vector3::Dot(particleA->GetVelocity(), contactNormal);
            particleA->Impulsion(restitution * mA * (-2) * uA * contactNormal); 
        }
        else
        {
            // Getting actual values
            double mA = particleA->GetMass();
            double mB = particleB->GetMass();
            double uA = Vector3::Dot(particleA->GetVelocity(), contactNormal);
            double uB = Vector3::Dot(particleB->GetVelocity(), contactNormal);
            // Computing new ones
            double constant = (mA * uA + mB * uB) / (mA + mB);
            double vA = restitution * mB * (uB - uA) / (mA + mB) + constant;
            double vB = restitution * mA * (uA - uB) / (mA + mB) + constant;
            // Making impulses
            particleA->Impulsion(mA * (vA - uA) * contactNormal);
            particleB->Impulsion(mB * (vB - uB) * contactNormal); 
        }   
    }


    void ParticleContact::Resolve()
    {
        ResolvePenetration();
        ResolveVelocity();
    }

} // namespace TooGoodEngine
