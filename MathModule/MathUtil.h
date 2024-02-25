#pragma once

struct MathUtil{
	static constexpr float PI = { 3.14159265358979323846f };
	static constexpr float TwoPI = { 2.f * PI };
	static constexpr float HalfPI = { 1.57079632679f };
	static constexpr float InvPI = { 0.31830988618f };
	static constexpr char InvalidHashName[] = "!@CK_INVALIDHASH#$";
	static const std::size_t InvalidHash;

	static constexpr int TruncToInt(float InFloat)
	{
		return (int)InFloat;
	}

	static constexpr int RountToInt(float InFloat)
	{
		return TruncToInt(roundf(InFloat));
	}

	static constexpr int FloorToInt(float InFloat)
	{
		return TruncToInt(floorf(InFloat));
	}

	static constexpr bool EqualsInTolerance(float InFloat1, float InFloat2, float InTolerance = SMALL_NUMBER)
	{
		return MathUtil::Abs(InFloat1 - InFloat2) <= InTolerance;
	}


	template< class T>
	static constexpr T Lerp(const T& InSrc, const T& InDest, float InAlpha)
	{
		return (T)(InSrc + InAlpha * (InDest - InSrc));
	}


	template<class T>
	static constexpr T Square(const T InNum)
	{
		return InNum * InNum;
	}

	static constexpr float Deg2Rad(float InDegree)
	{
		return InDegree * PI / 180.f;
	}

	static constexpr float Rad2Deg(float InRadian)
	{
		return InRadian * 180.f * InvPI;
	}


	template<class T>
	static constexpr T Max(const T A, const T B)
	{
		return (A >= B) ? A : B;
	}

	template<class T>
	static constexpr T Min(const T A, const T B)
	{
		return (A <= B) ? A : B;
	}

	template< class T >
	static T constexpr Max3(const T A, const T B, const T C)
	{
		return Max(Max(A, B), C);
	}

	template< class T >
	static T constexpr Min3(const T A, const T B, const T C)
	{
		return Min(Min(A, B), C);
	}

	template<class T>
	static constexpr T Abs(const T A)
	{
		return (A >= (T)0) ? A : -A;
	}

	template<class T>
	static constexpr T Clamp(const T X, const T Min, const T Max)
	{
		return X < Min ? Min : X < Max ? X : Max;
	}


	//나머지
	static float FMod(float X, float Y)
	{
		if (fabsf(Y) <= SMALL_NUMBER)
		{
			return 0.f;
		}

		const float quotient = (float)TruncToInt(X / Y);
		float intPortion = Y * quotient;
		if (fabsf(intPortion) > fabsf(X))
		{
			intPortion = X;
		}

		return (X - intPortion);
	}

	// 언리얼 엔진 코드에서 가져옴. 지정된 각도에 대한 두 삼각함수를 함께 가져오는 함수. 
	static constexpr void GetSinCosRad(float& OutSin, float& OutCos, float InRadian)
	{
		// Copied from UE4 Source Code
		// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
		float quotient = (InvPI * 0.5f) * InRadian;
		if (InRadian >= 0.0f)
		{
			quotient = (float)((int)(quotient + 0.5f));
		}
		else
		{
			quotient = (float)((int)(quotient - 0.5f));
		}
		float y = InRadian - (2.0f * PI) * quotient;

		// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
		float sign = 0.f;
		if (y > HalfPI)
		{
			y = PI - y;
			sign = -1.0f;
		}
		else if (y < -HalfPI)
		{
			y = -PI - y;
			sign = -1.0f;
		}
		else
		{
			sign = +1.0f;
		}

		float y2 = y * y;

		// 11-degree minimax approximation
		OutSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

		// 10-degree minimax approximation
		float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
		OutCos = sign * p;
	}


	static constexpr void GetSinCos(float& OutSin, float& OutCos, float InDegree)
	{
		if (InDegree == 0.f)
		{
			OutSin = 0.f;
			OutCos = 1.f;
		}
		else if (InDegree == 90.f)
		{
			OutSin = 1.f;
			OutCos = 0.f;
		}
		else if (InDegree == 180.f)
		{
			OutSin = 0.f;
			OutCos = -1.f;
		}
		else if (InDegree == 270.f)
		{
			OutSin = -1.f;
			OutCos = 0.f;
		}
		else
		{
			GetSinCosRad(OutSin, OutCos, MathUtil::Deg2Rad(InDegree));
		}
	}

};