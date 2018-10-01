#include "stdafx.h"
#include "utils.h"

namespace MY_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float a = endX - startX;
		float b = endY - startY;

		return sqrt(a * a + b * b);
	}

	float getAngle(float startX, float startY, float endX, float endY)
	{
		float a = endX - startX;
		float b = endY - startY;

		float d = sqrt(a * a + b * b);
		float angle = acosf(a / d);

		if (endY > startY)
		{
			angle = PI * 2 - angle;
		}

		return angle;
	}
}