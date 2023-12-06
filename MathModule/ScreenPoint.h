#pragma once
struct ScreenPoint {
public:
	__forceinline constexpr ScreenPoint() = default;
	__forceinline explicit constexpr ScreenPoint(int _ix, int _iy) : x(_ix), y(_iy) { }
	__forceinline explicit constexpr ScreenPoint(float _fx, float _fy) : x(Math::FloorToInt(_fx)), y(Math::FloorToInt(_fy)) { }
	__forceinline explicit constexpr ScreenPoint(const Vec2& _vec) : ScreenPoint(_vec.x, _vec.y) {}

	__forceinline constexpr ScreenPoint operator-(const ScreenPoint& _point) const;
	__forceinline constexpr ScreenPoint operator+(const ScreenPoint& _point) const;

	int x = 0;
	int y = 0;
};

__forceinline constexpr ScreenPoint ScreenPoint::operator-(const ScreenPoint& _point) const
{
	return ScreenPoint(x - _point.x, y - _point.y);
}
__forceinline constexpr ScreenPoint ScreenPoint::operator+(const ScreenPoint& _point) const
{
	return ScreenPoint(x + _point.x, y + _point.y);
}