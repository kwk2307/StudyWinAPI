#pragma once

struct Vec2 {
	static constexpr BYTE Dimension = 2;

	// ¸â¹öº¯¼ö
	union
	{
		struct
		{
			float x, y;
		};

		std::array<float, Dimension> Scalars = { 0.f, 0.f };
	};
public:
	__forceinline constexpr Vec2 operator +(const Vec2& _vOther) const{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}

	__forceinline constexpr Vec2 operator -(const Vec2& _vOther) const {
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	__forceinline constexpr  Vec2 operator *(const Vec2& _vOther) const {
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	__forceinline constexpr Vec2 operator /(const Vec2& _vOther) const {
		assert(!(_vOther.x == 0 || _vOther.y == 0));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}

public:
	__forceinline explicit constexpr Vec2() :
		x(0.f),
		y(0.f)
	{}

	__forceinline explicit constexpr Vec2(float _x, float _y) :
		x(_x),
		y(_y)
	{}

	__forceinline explicit constexpr Vec2(int _x, int _y) :
		x((float)_x),
		y((float)_y)
	{}
};