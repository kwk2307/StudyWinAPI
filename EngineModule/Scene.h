#pragma once
class Scene
{
public:
	Scene(const std::string& InName);
	~Scene() {}

public:
	//const std::vector<std::unique_ptr<Object>> GetObjects() const { return _Objects; }
	const std::string& GetName() const { return _Name; }
	std::size_t GetHash() const { return _Hash; }
	static Scene Invalid;

private:

public:

private:
	//std::vector<std::unique_ptr<Object>> _Objects;
	std::size_t _Hash;
	std::string _Name;
};

