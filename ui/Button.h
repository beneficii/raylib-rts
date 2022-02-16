#pragma once

#include "raylib.h"
#include <functional>

class Button
{
public:
	char* text;

	Button(Texture2D image, char* txt, Vector2 position, float scale, std::function<void()> action);
	Button(char* image, char* txt, Vector2 position, float scale, std::function<void()> action);
	~Button();
	virtual void Draw();
	virtual bool TryPress(Vector2 mousePoint);

protected:
	float _scale;
	Rectangle _rect;
	
	int _fontSize;
	Texture2D _background;

	std::function<void()> _action;
};
