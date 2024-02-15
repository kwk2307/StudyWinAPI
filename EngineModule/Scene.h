#pragma once
class Scene
{
public:
	Scene() = default;
	Scene(const std::string& InName) :_Name(InName) {
		_Hash = std::hash<std::string>()(_Name);
	}
	~Scene() {}

public:
	//const std::vector<std::unique_ptr<Object>> GetObjects() const { return _Objects; }
	const std::string& GetName() const { return _Name; }
	std::size_t GetHash() const { return _Hash; }
	static Scene Invalid;
	void Update(float InDeltaSeconds);

private:

public:

private:
	//std::vector<std::unique_ptr<Object>> _Objects;
	std::size_t _Hash;
	std::string _Name;
};

