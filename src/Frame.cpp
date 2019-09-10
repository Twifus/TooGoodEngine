#include "Frame.hpp"
/*#include <cstdio>
#include <cassert>
#include <stdexcept>
#include <unistd.h>
*/
namespace TooGoodEngine
{
	Frame::Frame()
	{
		lastFrame = time(NULL);
		deltaFrame = 0.0;
	}

	double Frame::getDeltaFrame() const
	{
		return deltaFrame;
	}

	void Frame::computeDeltaFrame()
	{
		std::time_t t = time(NULL);
		deltaFrame =(t - lastFrame);
		lastFrame = t;
	}
}

/*int main() 
{
	using namespace TooGoodEngine;

	Frame * f = new Frame();
	f->computeDeltaFrame();
	printf("delta frame : %f\n", f->getDeltaFrame());
	sleep(2);
	f->computeDeltaFrame();
	printf("delta frame : %f", f->getDeltaFrame());
	return EXIT_SUCCESS;
}*/