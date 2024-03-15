#pragma once

class SceneMngInterface
{
public:

	virtual const std::vector<std::shared_ptr<Object>>& GetCurrentScene(UINT InType) const = 0;

private:
};
