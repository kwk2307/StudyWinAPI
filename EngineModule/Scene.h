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
	// _VecInfo�� �ӽð�ü�� ���� �����ϴ� ���� �ƴ� ���� _VecInfo�� ���� �����ϱ� ���ؼ���
	// & �����ڷ� �����ؾ��Ѵ� �׷��� �����簡 �Ͼ�� ���� 
	// const Ű���带 �������μ� ���� �����Ǵ� ��� ���� �����Ѵ� 
	const std::vector<ObjectInfo>& GetInfo() const { return _VecInfo; }

	bool operator==(const Scene& InScene) const;
	bool operator!=(const Scene& InScene) const;

	void AddObject(const ObjectInfo& Ininfo);

	static Scene Invalid;
	
	// ���Ͽ��� �о�ͼ� VecInfo ����� ��� �߰� 
	
private:
	std::vector<ObjectInfo> _VecInfo;
	std::size_t _Hash;
	std::string _Name;
};

