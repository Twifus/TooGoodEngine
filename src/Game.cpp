#include "Particle.hpp"
#include "Frame.hpp"
#include "Vector3.hpp"

#define PARTICLES_LENGTH 3

void update(double deltatime, Particle& particle) 
{
	particle.Update(deltatime);
}

void display(Particle& particle)
{

}

int main() 
{
	Frame f = Frame();
	Particle p[] = { Particle(), Particle(0.7, 3), Particle(0.5, 5) };
	while (true) 
	{
		f.computeDeltaTime();

		//Loop for particles' position update
		for (size_t i = 0; i < PARTICLES_LENGTH; i++)
		{
			update(f.getDeltaTime(),&p[i]);
		}

		//Loop for particles display
		for (size_t i = 0; i < PARTICLES_LENGTH; i++)
		{
			display(&p[i]);
		}
	}
}