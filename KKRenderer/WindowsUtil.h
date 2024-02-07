#pragma once

namespace WindowsUtil {
	float GetCyclesPerMilliSeconds()
	{
		LARGE_INTEGER frequency;
		if (!QueryPerformanceFrequency(&frequency))
		{
			return 0.f;
		}

		return (float)(frequency.QuadPart / 1000.f);
	}

	long long GetCurrentTimeStamp()
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		return currentTime.QuadPart;
	}
};
