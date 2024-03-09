#pragma once

class Collider
{
public:
	Collider();
	~Collider();
public:

private:
	std::vector<Vector3> _Vertices;
	std::vector<size_t> _Indices;

};

