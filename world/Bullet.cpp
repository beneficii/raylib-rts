#include "Bullet.h"

#include "helpers/draw.h"
#include "world/Unit.h"
#include "Managers/GameState.h"

Bullet::Bullet(Vector2 position, int damage, std::weak_ptr<Unit> target)
{
	_position = position;
	_damage = damage;
	_target = target;

	_speed = 10;

	_texture = GameState::GetInstance()->images["bullet"];
}

Bullet::~Bullet()
{

}

void Bullet::Update()
{
	// if target died, we dispose of bullet
	if (_target.expired()) {
		Destroy();
		return;
	}

	auto target = _target.lock();

	_position = MoveTowardsV2(_position, target->position, _speed);

	// if we reached target, damage it and destroy the bullet
	if (IsSame(_position, target->position)) {
		target->Damage(_damage);
		Destroy();
	}
}

void Bullet::Draw()
{
	DrawTextureAtMid(_texture, _position, 1, BLACK);
}
