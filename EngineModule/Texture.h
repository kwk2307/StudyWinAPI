#pragma once
class Texture
{
public:
	Texture(std::string InFileName);
	~Texture() {}

public:
	void Release();
	bool IsIntialized() const { return (_Buffer.size() > 0); }

	Color GetSample(Vector2 InUV) const;

private:
	void LoadFromFile(FILE* f);

private:
	static constexpr BYTE Channel = 4;
	std::vector<Color> _Buffer;
	UINT32 _Width = 0;
	UINT32 _Height = 0;


};

