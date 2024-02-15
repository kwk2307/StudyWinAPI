#include "Precompiled.h"

Scene Scene::Invalid(MathUtil::InvalidHashName);

Scene::Scene(const std::string& InName) : _Name(InName) {
	_Hash = std::hash<std::string>()(_Name);
}
