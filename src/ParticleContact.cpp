#include "ParticleContact.hpp"

namespace TooGoodEngine
{
    ParticleContact::ParticleContact(Particle* a, Particle* b, float r)
    {
        restitution = r;
        particles[0] = a;
        particles[1] = b;
        contactNormal = (b == nullptr) ? Vector3::up : (a->position - b->position).Normalized();
        interpenetration = (b == nullptr) ? 0 :
                        b->GetRadius() + a->GetRadius() - (b->position - a->position).SquaredMagnitude();
    }

    ParticleContact::ParticleContact(Particle* a, float r) : ParticleContact(a,nullptr,r) {}

    double ParticleContact::ApprochVelocity() const
    {
        Vector3 vB = (particles[1] == nullptr) ? Vector3::zero : particles[1]->GetVelocity();
        return Vector3::Dot((vB - particles[0]->GetVelocity()), contactNormal);
    }

    void ParticleContact::ResolvePenetration()
    {
        if (particles[1] == nullptr)
        {
            particles[0]->position += interpenetration * contactNormal;
        }
        else
        {
            double mA = particles[0]->GetMass();
            double mB = particles[1]->GetMass();
            Vector3 tmp = (1 / (mA + mB) * interpenetration) * contactNormal;
            Vector3 deltaPosA = mB * tmp;
            Vector3 deltaPosB = -mA * tmp;
            particles[0]->position += deltaPosA;
            particles[1]->position += deltaPosB;
        } 
    }

    void ParticleContact::ResolveVelocity(double time)
    {
        if (particles[1])
        {
            // Getting actual values
            double mA = particles[0]->GetMass();
            double mB = particles[1]->GetMass();
            double uA = Vector3::Dot(particles[0]->GetVelocity(), contactNormal);
            double uB = Vector3::Dot(particles[1]->GetVelocity(), contactNormal);
            // Computing new ones
            double constant = (mA * uA + mB * uB) / (mA + mB);
            double vA = restitution * mB * (uB - uA) / (mA + mB) + constant;
            double vB = restitution * mB * (uA - uB) / (mA + mB) + constant;
            // Making impulses
            particles[0]->Impulsion(mA * (vA - uA) * contactNormal);
            particles[1]->Impulsion(mB * (vB - uB) * contactNormal);
        }
        else
        {
            double mA = particles[0]->GetMass();
            double uA = Vector3::Dot(particles[0]->GetVelocity(), contactNormal);
            particles[0]->Impulsion(2 * mA * uA * contactNormal);
        }

        
    }

    void ParticleContact::Resolve(double time)
    {
        // ResolvePenetration();
        ResolveVelocity(time);
    }

} // namespace TooGoodEngine
