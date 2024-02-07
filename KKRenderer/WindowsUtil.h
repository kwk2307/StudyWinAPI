#pragma once

namespace WindowsUtil {

	// Ÿ�̸��� �ֱ⸦ �˾ƿ�
	float GetCyclesPerMilliSeconds()
	{
		LARGE_INTEGER frequency;
		if (!QueryPerformanceFrequency(&frequency))
		{
			return 0.f;
		}

		return (float)(frequency.QuadPart / 1000.f);
	}

	// ���� Ÿ�̸� ��ġ�� �˷���
	long long GetCurrentTimeStamp()
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		return currentTime.QuadPart;
	}
};
