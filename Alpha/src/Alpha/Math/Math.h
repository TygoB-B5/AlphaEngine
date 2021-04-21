#pragma once

namespace Math
{
	struct Mathf
	{
		static float Clamp(const float& value, const float& minValue, const float& maxValue)
		{
			if (minValue < minValue)
				return 0;

			if (minValue > maxValue)
				return 1;

			return value;
		}
	};

	struct Mathi
	{
		static int Clamp(const int& value, const int& minValue, const int& maxValue)
		{
			if (minValue < minValue)
				return 0;

			if (minValue > maxValue)
				return 1;

			return value;
		}
	};
}