#pragma once

enum class BoundCheckResult : UINT32
{
	Outside = 0,
	Intersect,
	Inside
};

struct Frustum
{
	// 생성자
	__forceinline constexpr Frustum() = default;
	__forceinline constexpr Frustum(const std::array<Plane, 6>& InPlanes) :Planes(InPlanes) {}

	// 멤버함수 
	__forceinline constexpr BoundCheckResult CheckBound(const Vector3& InPoint) const;
	__forceinline constexpr BoundCheckResult CheckBound(const Sphere& InSphere) const;
	__forceinline constexpr BoundCheckResult CheckBound(const Box& InBox) const;
	__forceinline constexpr bool IsIntersect(const Box& InBox) const;

	// 멤버변수
	std::array<Plane, 6> Planes; // Y+, Y-, X+, X-, Z+, Z- 순으로 저장
};

__forceinline constexpr BoundCheckResult Frustum::CheckBound(const Vector3& InPoint) const {

	for (const auto& p : Planes)
	{
		if (p.IsOutside(InPoint))
		{
			return BoundCheckResult::Outside;
		}
		else if (MathUtil::EqualsInTolerance(p.Distance(InPoint), 0.f))
		{
			return BoundCheckResult::Intersect;
		}
	}
	return BoundCheckResult::Inside;
}

__forceinline constexpr BoundCheckResult Frustum::CheckBound(const Sphere& InSphere) const{
	for (const auto& p : Planes)
	{
		if (p.Distance(InSphere.Center) > InSphere.Radius)
		{
			return BoundCheckResult::Outside;
		}
		else if (MathUtil::Abs(p.Distance(InSphere.Center)) <= InSphere.Radius)
		{
			return BoundCheckResult::Intersect;
		}

	}

	return BoundCheckResult::Inside;
}

__forceinline constexpr BoundCheckResult Frustum::CheckBound(const Box& InBox) const
{
	for (const auto& p : Planes)
	{
		Vector3 pPoint = InBox.Min, nPoint = InBox.Max;
		if (p.Normal.X >= 0.f) { pPoint.X = InBox.Max.X; nPoint.X = InBox.Min.X; }
		if (p.Normal.Y >= 0.f) { pPoint.Y = InBox.Max.Y; nPoint.Y = InBox.Min.Y; }
		if (p.Normal.Z >= 0.f) { pPoint.Z = InBox.Max.Z; nPoint.Z = InBox.Min.Z; }

		if (p.Distance(nPoint) > 0.f)
		{
			return BoundCheckResult::Outside;
		}
		if (p.Distance(nPoint) <= 0.f && p.Distance(pPoint) >= 0.f)
		{
			return BoundCheckResult::Intersect;
		}
	}

	return BoundCheckResult::Inside;
}

__forceinline constexpr bool Frustum::IsIntersect(const Box& InBox) const
{
	for (const auto& p : Planes)
	{
		Vector3 pVertex = InBox.Min, nVertex = InBox.Max;
		if (p.Normal.X >= 0.f) { pVertex.X = InBox.Max.X; nVertex.X = InBox.Min.X; }
		if (p.Normal.Y >= 0.f) { pVertex.Y = InBox.Max.Y; nVertex.Y = InBox.Min.Y; }
		if (p.Normal.Z >= 0.f) { pVertex.Z = InBox.Max.Z; nVertex.Z = InBox.Min.Z; }

		if (p.Distance(nVertex) <= 0.f && p.Distance(pVertex) >= 0.f)
		{
			return true;
		}
	}

	return false;
}
