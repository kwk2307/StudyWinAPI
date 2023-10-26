#pragma once

struct Vec2 {
	float x;
	float y;

public:
	Vec2& operator = (POINT _pt) {
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2 operator +(const Vec2& _vOther) {
		return Vec2(x + _vOther.x, y + _vOther.y);
	}

	Vec2 operator -(const Vec2& _vOther) {
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	Vec2 operator *(const Vec2& _vOther) {
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	Vec2 operator /(const Vec2& _vOther) {
		assert(!(_vOther.x == 0 || _vOther.y == 0));
		return Vec2(x + _vOther.x, y + _vOther.y);
	}



public:
	Vec2():
		x(0.f),
		y(0.f)
	{}

	Vec2(float _x, float _y):
		x(_x),
		y(_y)
	{}

	Vec2(int _x, int _y):
		x((float)_x),
		y((float)_y)
	{}


};