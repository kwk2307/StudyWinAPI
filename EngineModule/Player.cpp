#include "Precompiled.h"

Player::Player(const ObjectInfo& Info):
	Object(Info)
{
}

void Player::Update(float InDeltaSeconds)
{
	//ÁÂ¿ì ¿òÁ÷ÀÓ
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
		if (isLand) {
			_Speed.Y = 300.f;
		}
	}
	if (!isLand) {
		_Speed += Vector3(0.f, -10.f, 0.f);
	}
	
	GetTransform().AddPosition(_Speed * InDeltaSeconds);
}

void Player::OnCollision(const Collider& InOther)
{
}

void Player::BeginCollision(const Collider& InOther)
{
	if (InOther.GetOwner().GetType() == ObjectType::Block) {
		isLand = true;
		_Speed.Y = 0;
	}
}

void Player::EndCollision(const Collider& InOther)
{
	isLand = false;
}

