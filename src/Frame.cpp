#include ннн<ctime>
#include "Frame.hpp"

namespace TooGoodEngine
{
	Frame::Frame()
	{
		this.lastFrame = 0;
		this.deltaFrame = 0;
	}

	double Frame::getDeltaFrame() const
	{
		return this.deltaFrame;
	}

	void Frame::computeDeltaFrame() const
	{
		clock_t t = clock();
		this.deltaFrame = (double)(t - this.lastFrame) / CLOCKS_PER_SECOND;
		this.lastFrame = t;
	}
}