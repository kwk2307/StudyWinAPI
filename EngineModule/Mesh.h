#pragma once
enum class MeshType
{
	Normal,

};

class Mesh {

public:

	__forceinline bool HasUV() const { return _UVs.size() > 0; }

	std::vector<Vector3>& GetVertices() { return _Vertices; }
	const std::vector<Vector3>& GetVertices() const { return _Vertices; }
	std::vector<size_t>& GetIndices() { return _Indices; }
	const std::vector<size_t>& GetIndices() const { return _Indices; }
	std::vector<Vector2>& GetUVs() { return _UVs; }
	const std::vector<Vector2>& GetUVs() const { return _UVs; }

private:
	std::vector<Vector3> _Vertices;
	std::vector<size_t> _Indices;
	std::vector<Vector2> _UVs;

	MeshType _MeshType = MeshType::Normal;

};