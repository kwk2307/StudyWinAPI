#pragma once
struct Screen {
public:
	__forceinline constexpr Screen() = default;
	__forceinline explicit constexpr Screen(int _ix, int _iy) : x(_ix), y(_iy) { }
	__forceinline explicit constexpr Screen(float _fx, float _fy) : x(Math::FloorToInt(_fx)), y(Math::FloorToInt(_fy)) { }
	__forceinline explicit constexpr Screen(const Vec2& _vec) : Screen(_vec.x, _vec.y) {}

	__forceinline constexpr Screen operator-(const Screen& _sScreen) const;
	__forceinline constexpr Screen operator+(const Screen& _sScreen) const;

	int x = 0;
	int y = 0;
};

__forceinline constexpr Screen Screen::operator-(const Screen& _sScreen) const
{
	return Screen(x - _sScreen.x, y - _sScreen.y);
}
__forceinline constexpr Screen Screen::operator+(const Screen& _sScreen) const
{
	return Screen(x + _sScreen.x, y + _sScreen.y);
}