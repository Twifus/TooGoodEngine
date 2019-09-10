#include "Particle.hpp"
#include "Frame.hpp"
#include "Vector3.hpp"

#include <iostream>

#define PARTICLES_LENGTH 3

using namespace TooGoodEngine;


void display(Particle& particle)
{
	std::cout << particle.position << std::endl;
}

int main() 
{
	Frame f = Frame();
	Particle p[] = { Particle(), Particle(0.7, 3), Particle(0.5, 5) };
	bool stop = false;
	while (!stop) 
	{
		f.computeDeltaFrame();

		//Loop for particles' position update
		for (auto &i : p)
		{
			i.Update(f.getDeltaFrame());
		}

		//Loop for particles display
		for (size_t i = 0; i < PARTICLES_LENGTH; i++)
		{
			display(p[i]);
		}
	}
}