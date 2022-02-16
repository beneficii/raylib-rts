#include "FloatingText.h"
#include "helpers/draw.h"

FloatingText::FloatingText(Vector2 position, std::string message, Color color, int fontSize, float distance, double lifetime)
{
	_position = position;
	_message = message;
	_color = color;
	_fontSize = fontSize;
	_distance = distance;
	_lifetime = lifetime;
	_startTime = GetTime();
}

void FloatingText::Update()
{
	// nothing
}

void FloatingText::Draw()
{
	// normalized time since this floater existed
	double time = (GetTime() - _startTime) / _lifetime;
	
	if (time > 1) {			// meaning we exceeded lifetime
		Destroy();
		return;
	}

	auto pos = _position;
	pos.y -= _distance * time;

	DrawTextAtMid(_message.c_str(), { pos.x + 1, pos.y + 1 }, _fontSize, Color{ 0,0,0,50 }); // add some shadow
	DrawTextAtMid(_message.c_str(), pos, _fontSize, _color);
}
