#pragma once
class Scene
{
public:
	const std::vector<Object*> GetObjects() { return _vecObject; }
private:

public:

private:
	std::vector<Object*> _vecObject;

};

