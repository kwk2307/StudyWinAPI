#pragma once
class CollisionMngInterface {

public:
	virtual void Update(float InDeltaSeconds) = 0;
	virtual void CheckGroup(ObjectType InLeft, ObjectType InRight) = 0;

};