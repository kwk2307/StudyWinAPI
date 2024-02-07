#pragma once

namespace WindowsUtil {

	// 타이머의 주기를 알아옴
	float GetCyclesPerMilliSeconds()
	{
		LARGE_INTEGER frequency;
		if (!QueryPerformanceFrequency(&frequency))
		{
			return 0.f;
		}

		return (float)(frequency.QuadPart / 1000.f);
	}

	// 현재 타이머 수치를 알려줌
	long long GetCurrentTimeStamp()
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		return currentTime.QuadPart;
	}
};
