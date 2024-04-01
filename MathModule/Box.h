#pragma once
struct Box
{
public:
	__forceinline constexpr Box() = default;
	__forceinline constexpr Box(const Box& InBox) : Min(InBox.Min), Max(InBox.Max) { }
	__forceinline constexpr Box(const Vector3& InMinVector, const Vector3& InMaxVector) : Min(InMinVector), Max(InMaxVector) { }
	Box(const std::vector<Vector3> InVertices);

	__forceinline constexpr bool Intersect(const Box& InBox) const;
	__forceinline constexpr bool IsInside(const Box& InBox) const;
	__forceinline constexpr bool IsInside(const Vector3& InVector) const;

	__forceinline constexpr Box operator+=(const Vector3& InVector);
	__forceinline constexpr Box operator+=(const Box& InBox);

	__forceinline constexpr Vector3 GetSize() const;
	__forceinline constexpr Vector3 GetExtent() const;
	__forceinline constexpr void GetCenterAndExtent(Vector3& OutCenter, Vector3& OutExtent) const;

	__forceinline std::vector<Vector3> GetVertices() const;
public:
	Vector3 Min;
	Vector3 Max;
};

__forceinline constexpr bool Box::Intersect(const Box& InBox) const
{
	if ((Min.X > InBox.Max.X) || (InBox.Min.X > Max.X))
	{
		return false;
	}

	if ((Min.Y > InBox.Max.Y) || (InBox.Min.Y > Max.Y))
	{
		return false;
	}

	if ((Min.Z > InBox.Max.Z) || (InBox.Min.Z > Max.Z))
	{
		return false;
	}

	return true;
}

__forceinline constexpr bool Box::IsInside(const Box& InBox) const
{
	return (IsInside(InBox.Min) && IsInside(InBox.Max));
}

__forceinline constexpr bool Box::IsInside(const Vector3& InVector) const
{
	return ((InVector.X >= Min.X) && (InVector.X <= Max.X) && (InVector.Y >= Min.Y) && (InVector.Y <= Max.Y) && (InVector.Z >= Min.Z) && (InVector.Z <= Max.Z));
}

__forceinline constexpr Box Box::operator+=(const Vector3& InVector)
{
	Min.X = MathUtil::Min(Min.X, InVector.X);
	Min.Y = MathUtil::Min(Min.Y, InVector.Y);
	Min.Z = MathUtil::Min(Min.Z, InVector.Z);

	Max.X = MathUtil::Max(Max.X, InVector.X);
	Max.Y = MathUtil::Max(Max.Y, InVector.Y);
	Max.Z = MathUtil::Max(Max.Z, InVector.Z);

	return *this;
}

__forceinline constexpr Box Box::operator+=(const Box& InBox)
{
	Min.X = MathUtil::Min(Min.X, InBox.Min.X);
	Min.Y = MathUtil::Min(Min.Y, InBox.Min.Y);
	Min.Z = MathUtil::Min(Min.Z, InBox.Min.Z);

	Max.X = MathUtil::Max(Max.X, InBox.Max.X);
	Max.Y = MathUtil::Max(Max.Y, InBox.Max.Y);
	Max.Z = MathUtil::Max(Max.Z, InBox.Max.Z);
	return *this;
}

__forceinline constexpr Vector3 Box::GetSize() const
{
	return (Max - Min);
}

__forceinline constexpr Vector3 Box::GetExtent() const
{
	return GetSize() * 0.5f;
}

__forceinline constexpr void Box::GetCenterAndExtent(Vector3& OutCenter, Vector3& OutExtent) const
{
	OutExtent = GetExtent();
	OutCenter = Min + OutExtent;
}

__forceinline std::vector<Vector3> Box::GetVertices() const 
{
	std::vector<Vector3> result = {
		Vector3(Min.X,Min.Y,Min.Z),
		Vector3(Max.X,Min.Y,Min.Z),
		Vector3(Max.X,Max.Y,Min.Z),
		Vector3(Min.X,Max.Y,Min.Z),
		Vector3(Min.X,Min.Y,Max.Z),
		Vector3(Max.X,Min.Y,Max.Z),
		Vector3(Max.X,Max.Y,Max.Z),
		Vector3(Min.X,Max.Y,Max.Z)
	};

	return result;
}