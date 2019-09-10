#include "Frame.hpp"
#include <ctime>

namespace TooGoodEngine
{
	Frame::Frame()
	{
		lastFrame = 0;
		deltaFrame = 0;
	}

	double Frame::getDeltaFrame() const
	{
		return deltaFrame;
	}

	void Frame::computeDeltaFrame()
	{
		std::clock_t t = clock();
		deltaFrame = (double)(t - lastFrame) / CLOCKS_PER_SEC;
		lastFrame = t;
	}
}