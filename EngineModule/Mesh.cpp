#include "Precompiled.h"

Mesh::Mesh(std::string InName,std::vector<Vector3*> InVertices, std::vector<size_t> Indices, std::vector<Vector2*> InUVs):
	_Name(InName),
	_Vertices(InVertices),
	_Indices(Indices),
	_UVs(InUVs)
{

}

Mesh::~Mesh()
{
	//데이터 해제 해줘야함
	Safe_Erase_Vecter(_Vertices);
	Safe_Erase_Vecter(_UVs);
}
