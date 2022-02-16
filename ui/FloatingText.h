#pragma once

#include "raylib.h"
#include "world/WorldObject.h"


#include <string>

class FloatingText : public WorldObject
{
public:
	FloatingText(Vector2 position, std::string message, Color color = BLACK, int fontSize = 11, float distance = 16, double lifetime = 0.2);

	void Update();
	void Draw();

private:
	std::string _message;
	double _startTime;
	double _lifetime;
	float _distance;
	Color _color;
	Vector2 _position;
	int _fontSize;
};

