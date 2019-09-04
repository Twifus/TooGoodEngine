#pragma once

namespace TooGoddEngine
{
	class Frame
	{
	private:
		double lastFrame;
		double deltaFrame;

	public:
		void computeDeltaFrame() const;
		double getDeltaFrame() const;
	};
}