#include "Precompiled.h"


Object::Object(const ObjectInfo& Info):
	_ObjectType(Info.type),
	_Transform(Info.transform)
{
}

void Object::Update(float InDeltaSeconds)
{
}

