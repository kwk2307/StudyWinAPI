#pragma once
class Scene
{
public:
	Scene(const std::string& InName) :_Name(InName) {
		_Hash = std::hash<std::string>()(_Name);
	}
	~Scene() {}

public:
	const std::string& GetName() const { return _Name; }
	std::size_t GetHash() const { return _Hash; }
	// _VecInfo를 임시객체로 만들어서 리턴하는 것이 아닌 실제 _VecInfo의 값을 전달하기 위해서는
	// & 참조자로 리턴해야한다 그래야 값복사가 일어나지 않음 
	// const 키워드를 넣음으로서 값이 수정되는 경우 또한 제한한다 
	const std::vector<ObjectInfo>& GetInfo() const { return _VecInfo; }

	bool operator==(const Scene& InScene) const;
	bool operator!=(const Scene& InScene) const;

	void AddObject(const ObjectInfo& Ininfo);

	static Scene Invalid;
	
	// 파일에서 읽어와서 VecInfo 만드는 기능 추가 
	
private:
	std::vector<ObjectInfo> _VecInfo;
	std::size_t _Hash;
	std::string _Name;
};

