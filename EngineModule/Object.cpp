#include "Precompiled.h"


Object::Object(const ObjectInfo& Info):
	_ObjectType(Info.type),
	_Transform(Info.transform)
{
	if (Info.Mesh != "") {
		_Meshkey = std::hash<std::string>()(Info.Mesh);
	}

	if (Info.Texture != "") {
		_Texturekey = std::hash<std::string>()(Info.Texture);
	}
}

void Object::Update(float InDeltaSeconds)
{
	
}

