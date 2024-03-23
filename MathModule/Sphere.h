#pragma once
struct Sphere
{
public:
	__forceinline constexpr Sphere() = default;
	__forceinline constexpr Sphere(const Circle& InCircle) 
		: Center(InCircle.Center), Radius(InCircle.Radius) {};
	Sphere(const std::vector<Vector3>& InVertices);

	__forceinline constexpr bool IsInside(const Vector3& InVector) const;
	__forceinline constexpr bool Intersect(const Sphere& InCircle) const;

public:
	Vector3 Center = Vector3::Zero;
	float Radius = 0.f;
};

__forceinline constexpr bool Sphere::IsInside(const Vector3& InVector) const
{
	return ((Center - InVector).SizeSquared() <= (Radius * Radius));
}

__forceinline constexpr bool Sphere::Intersect(const Sphere& InCircle) const
{
	float radiusSum = Radius + InCircle.Radius;
	return (Center - InCircle.Center).SizeSquared() <= (radiusSum * radiusSum);
}