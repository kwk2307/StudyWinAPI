#pragma once
struct Circle
{
public:
	__forceinline constexpr Circle() = default;
	__forceinline constexpr Circle(const Circle& InCircle) 
		: Center(InCircle.Center), Radius(InCircle.Radius) {};
	Circle(const std::vector<Vector2> InVertices);

	__forceinline constexpr bool IsInside(const Vector2& InVector) const;
	__forceinline constexpr bool Intersect(const Circle& InCircle) const;

public:
	Vector2 Center = Vector2::Zero;
	float Radius = 0.f;
};

__forceinline constexpr bool Circle::IsInside(const Vector2& InVector) const
{
	return ((Center - InVector).SizeSquared() <= (Radius * Radius));
}

__forceinline constexpr bool Circle::Intersect(const Circle& InCircle) const
{
	float twoRadiusSum = Radius + InCircle.Radius;
	return (Center - InCircle.Center).SizeSquared() <= (twoRadiusSum * twoRadiusSum);
}