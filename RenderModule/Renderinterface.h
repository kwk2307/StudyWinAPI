#pragma once
class Renderinterface
{
public:
	virtual bool Init(const Screen& InSize) = 0;
	virtual void Shutdown() = 0;
	virtual bool IsInitialized() const = 0;

	//virtual void Clear(const LinearColor& InClearColor) = 0;
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;

	//virtual void DrawPoint(const Vec2& InVectorPos, const LinearColor& InColor) = 0;
	//virtual void DrawPoint(const Screen& InScreenPos, const LinearColor& InColor) = 0;
	//virtual void DrawLine(const Vec2& InStartPos, const Vec2& InEndPos, const LinearColor& InColor) = 0;
	//virtual void DrawLine(const Vector4& InStartPos, const Vector4& InEndPos, const LinearColor& InColor) = 0;

	virtual float GetDepthBufferValue(const Screen& InScreenPos) const = 0;
	virtual void SetDepthBufferValue(const Screen& InScreenPos, float InDepthValue) = 0;

	//virtual void DrawFullVerticalLine(int InX, const LinearColor& InColor) = 0;
	//virtual void DrawFullHorizontalLine(int InY, const LinearColor& InColor) = 0;

	//virtual void PushStatisticText(std::string&& InText) = 0;
	//virtual void PushStatisticTexts(std::vector<std::string>&& InTexts) = 0;
};

