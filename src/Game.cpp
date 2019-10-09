#include <algorithm>
#include <functional>
#include <iostream>
#include <SDL.h>
#include <tuple>
#include <vector>

#include "AnchoredSpringForceGenerator.hpp"
#include "BungeeSpringForceGenerator.hpp"
#include "BuoyancyForceGenerator.hpp"
#include "DragForceGenerator.hpp"
#include "Frame.hpp"
#include "ForcesRegistery.hpp"
#include "GameSDL.hpp"
#include "GravityForceGenerator.hpp"
#include "Particle.hpp"
#include "ParticleContact.hpp"
#include "ParticleContactResolver.hpp"
#include "ParticleForceGenerator.hpp"
#include "SpringForceGenerator.hpp"
#include "Sprite.hpp"
#include "StiffSpringForceGenerator.hpp"
#include "Vector3.hpp"

using namespace TooGoodEngine;

void initParticles1(GameSDL& sdl, std::vector<Particle>& particles)
{
	Particle stone  = Particle(1, 0.1, Vector3(-3, 0, 0), Vector3(10, 5, 0));
	Particle bullet = Particle(3, 0.3, Vector3(0, 0, 0), Vector3( 0, 5, 0));
	Particle rocket = Particle(5, 0.5, Vector3(3, 0, 0), Vector3( 0, 5, 0));

	particles = { stone, bullet, rocket };

	sdl.CreateSprite(&particles[0], "sprites/red_circle.png");
	sdl.CreateSprite(&particles[1], "sprites/white_circle.png");
	sdl.CreateSprite(&particles[2], "sprites/green_circle.png");
}

void addForces1(ForcesRegistery& registry, std::vector<Particle>& particles)
{
	static GravityForceGenerator gravityGenerator;
	for (auto& i : particles)
	{
		registry.Add(i, gravityGenerator);
	}
}

void addCollisions1(ParticleContactResolver& resolver, std::vector<Particle>& particles)
{
	for (auto p1 = particles.begin(); p1 < particles.end(); p1++)
	{
		for (auto p2 = p1 + 1; p2 < particles.end(); p2++)
		{
			if ((p1->position - p2->position).Magnitude() <= p1->GetRadius() + p2->GetRadius())
			{
				resolver.AddContact(ParticleContact(&(*p1), &(*p2), 0.95));
			}
		}
		if (p1->position.y <= -3)
			resolver.AddContact(ParticleContact(&(*p1), -3 * Vector3::up, Vector3::up, 0.9));
	}
}

void initParticles2(GameSDL& sdl, std::vector<Particle>& particles)
{
	particles = {
		Particle(1, 0.2, Vector3(-5, 2.5, 0), Vector3(0, -2, 0)), // Anchored Spring

		Particle(std::numeric_limits<double>::infinity(), 0.2, Vector3(-2.5, 3, 0)), // Bungee Spring (1)
		Particle(1, 0.2, Vector3(-2.5, 2.5, 0), Vector3(0, -2, 0)), // Bungee Spring (2)

		Particle(1, 0.2, Vector3(0, 3, 0)), // Buoyancy

		Particle(1, 0.2, Vector3(2.5, 3, 0), Vector3(0, 2, 0)), // Spring (1)
		Particle(1, 0.2, Vector3(2.5, -3, 0), Vector3(0, -2, 0)), // Spring (2)

		Particle(1, 0.2, Vector3(5, 3, 0), Vector3(0, -2, 0)) // Stiff Spring
	};

	for (int i = 0; i < particles.size(); ++i)
	{
		if (i % 2 == 0)
			sdl.CreateSprite(&particles[i], "sprites/red_circle.png");
		else
			sdl.CreateSprite(&particles[i], "sprites/green_circle.png");
	}
}

void addForces2(ForcesRegistery& registry, std::vector<Particle>& particles)
{
	static GravityForceGenerator gravGen;
	static DragForceGenerator dragGen(0.01, 0.1);
	static AnchoredSpringForceGenerator anchoredGen(Vector3(-5, 3, 0), 10, 3);
	static BungeeSpringForceGenerator bungeeGen1(particles[2], 10, 4.5);
	static BungeeSpringForceGenerator bungeeGen2(particles[1], 10, 4.5);
	static BuoyancyForceGenerator buyoGen(0.4, 0.033, 0, 1000);
	static SpringForceGenerator springGen1(particles[5], 10, 4.5);
	static SpringForceGenerator springGen2(particles[4], 10, 4.5);
	static StiffSpringForceGenerator stiffGen(Vector3(5, 0, 0), 10, 0.99);
	
	registry.Add(particles[0], anchoredGen);
	registry.Add(particles[0], gravGen);
	registry.Add(particles[0], dragGen);

	registry.Add(particles[1], bungeeGen1);
	registry.Add(particles[1], dragGen);
	registry.Add(particles[2], bungeeGen2);
	registry.Add(particles[2], gravGen);
	registry.Add(particles[2], dragGen);

	registry.Add(particles[3], buyoGen);
	registry.Add(particles[3], gravGen);
	registry.Add(particles[3], dragGen);

	registry.Add(particles[4], springGen1);
	registry.Add(particles[4], dragGen);
	registry.Add(particles[5], springGen2);
	registry.Add(particles[5], dragGen);

	registry.Add(particles[6], stiffGen);
}

int main (int argc, char* argv[])
{
	std::function<void(GameSDL&, std::vector<Particle>&)> InitParticles = [](auto&, auto&) {};
	std::function<void(ForcesRegistery&, std::vector<Particle>&)> AddForces = [](auto&, auto&) {};
	std::function<void(ParticleContactResolver&, std::vector<Particle>&)> AddCollisions = [](auto&, auto&) {};
	
	std::cout << "Type a number + 'Enter' to select a mode:\n" <<
		"\t1 - Basic collision. 3 spheres collide with each other.\n" <<
		"\t2 - Spring showcase (AnchoredSpring, BungeeSpring, Buoyancy, Spring and StiffSpring)" << std::endl;
	char c = std::cin.get();
	if (c == '1')
	{
		InitParticles = initParticles1;
		AddForces = addForces1;
		AddCollisions = addCollisions1;
	}
	else if (c == '2')
	{
		InitParticles = initParticles2;
		AddForces = addForces2;
	}

	GameSDL gameSDL = GameSDL();
	std::vector<Particle> particles;

	InitParticles(gameSDL, particles);

	Frame f = Frame();
	ParticleContactResolver contactResolver;
	ForcesRegistery registry;

	////////////////
	// EVENT LOOP //
	while (1)
	{
		int exit = gameSDL.HandleEvents();
		if (exit == -1)
			break;

		// Measure deltaTime since last frame
		f.computeDeltaFrame();
		
		AddCollisions(contactResolver, particles);
		contactResolver.Resolve();
		contactResolver.Clear();

		AddForces(registry, particles);
		registry.UpdateForces(f.getDeltaFrame());
		registry.Clear();
		
		// Update each particle position
		for (auto &i : particles)
		{
			i.Update(f.getDeltaFrame());
			i.ClearForces();
		}

		gameSDL.render();
	}
	// EVENT LOOP //
	////////////////

    return EXIT_SUCCESS;
}
