#pragma once
#define MAX_SPEED 300

class Player :
    public Object
{
public:
    Player(const ObjectInfo& Info);

public:
    void Update(float InDeltaSeconds) override;

private:
    Vector3 _Speed = Vector3::Zero;
    
    bool isJump = false;
};

