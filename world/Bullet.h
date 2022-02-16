#pragma once

#include "raylib.h"
#include "world/WorldObject.h"
#include <memory>

class Unit;


class Bullet : WorldObject
{
public:
	Bullet(Vector2 position, int damage, std::weak_ptr<Unit> target);
	~Bullet();
	void Update();
	void Draw();

private:
	int _damage;
	std::weak_ptr<Unit> _target;
	Vector2 _position;

	float _speed;
	Texture2D _texture;
	
};

