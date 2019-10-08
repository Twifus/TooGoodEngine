#include "ParticleContact.hpp"

namespace TooGoodEngine
{
    ParticleContact::ParticleContact() {}
    ParticleContact::~ParticleContact() {}

    double ParticleContact::ApprochVelocity()
    {
        return Vector3::Dot((particles[1]->GetVelocity() - particles[0]->GetVelocity()), contactNormal);
    }

    void ParticleContact::ResolveVelocity(double time)
    {
        double restitutionCoef = restitution * ApprochVelocity();
        // oula c pas ça en dessous
        particles[0]->Impulsion(particles[0]->GetMass() * restitutionCoef * contactNormal);
        particles[1]->Impulsion(particles[1]->GetMass() * restitutionCoef * contactNormal);
    }

    void ParticleContact::ResolvePenetration(double time)
    {
        double mA = particles[0]->GetMass();
        double mB = particles[1]->GetMass();
        Vector3 tmp = (1 / (mA + mB) * interpenetration) * contactNormal;
        Vector3 deltaPosA = mB * tmp;
        Vector3 deltaPosB = -mA * tmp;
    }

    void ParticleContact::Resolve(double time)
    {
        ResolveVelocity(time);
        ResolvePenetration(time);
    }

} // namespace TooGoodEngine
