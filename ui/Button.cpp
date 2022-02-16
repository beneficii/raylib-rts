#include "Button.h"

#include "helpers/draw.h"
#include <iostream>
#include "Managers/GameState.h"

Button::Button(Texture2D image, char* txt, Vector2 position, float scale, std::function<void()> action)
{
	_background = image;

	text = txt;
	_scale = scale;
	_fontSize = 7;

	float width = _background.width * scale;
	float height = _background.height * scale;

	_rect = {
		position.x - width/2, // let position be centred
		position.y - height/2,
		width,
		height
	};

	_action = action;
}

Button::Button(char* image, char* txt, Vector2 position, float scale, std::function<void()> action)
	: Button(GameState::GetInstance()->images.at(image), txt, position, scale, action)
{
}

Button::~Button()
{
}

void Button::Draw()
{
	DrawTextureEx(_background, {_rect.x, _rect.y}, 0, _scale, WHITE); // Draw button background

	int fontSize = _fontSize * _scale;

	float midWidth = _rect.x + _background.width * _scale / 2;
	float midHeight = _rect.y + _background.height * _scale / 2;
	
	// add some padding and draw text inside a button
	DrawTextAtMid(text, { midWidth, midHeight }, fontSize, BLACK);
}


bool Button::TryPress(Vector2 mousePoint)
{
	if (CheckCollisionPointRec(mousePoint, _rect)) {
		if (_action != nullptr) {
			_action();
		}
		return true;
	}

	return false;
}