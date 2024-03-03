#include "Precompiled.h"

Player::Player(const ObjectInfo& Info):
	Object(Info)
{
}

void Player::Update(float InDeltaSeconds)
{
	//�¿� ������
	float XAixs = InputManager::GetInstanc().GetXAxis();
	if (MathUtil::Abs(XAixs) > 0.1f ){
		if (MathUtil::Abs(XAixs) < MAX_SPEED) {
			_Speed += Vector3(XAixs, 0.f, 0.f);
		}
	}
	else {
		if (_Speed.X < 0) {
			_Speed += Vector3::UnitX;
		}
		else if (_Speed.X > 0) {
			_Speed -= Vector3::UnitX;
		}
	}
	
 	if (InputManager::GetInstanc().GetKeyState(Key::SPACE) == KeyState::TAP) {
		if (!isJump) {
			isJump = true;
			_Speed.Y = 300.f;
		}
	}

	// �켱 �ٴ��� �����ϱ� ������ 
	if (GetTransform().GetPosition().Y > -100.f) {
		_Speed += Vector3(0.f, -10.f, 0.f);
	}
	else {
		if (_Speed.Y < 0.f) {
			_Speed.Y = 0.f;		
		}
		if (isJump) {
			isJump = false;
		}
	}

	GetTransform().AddPosition(_Speed * InDeltaSeconds);
}
