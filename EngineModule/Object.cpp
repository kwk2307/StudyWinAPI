#include "Precompiled.h"


Object::Object(const ObjectInfo& Info):
	_ObjectType(Info.type),
	_Transform(Info.transform),
	_Meshkey(Info.MeshKey)
{
}

void Object::Update(float InDeltaSeconds)
{
}

