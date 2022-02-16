#include "ViewMenu.h"

#include "ViewPlay.h"
#include "helpers/draw.h"
#include <iostream>
#include "Managers/GameState.h";


void MenuPlay()
{
	GameState::GetInstance()->SetView(new ViewPlay());
}

ViewMenu::ViewMenu()
{
	buttons.push_back(new Button(
		GameState::GetInstance()->images.at("button"),
		"Start",
		{ 480,270 },
		5,
		MenuPlay));
}

ViewMenu::~ViewMenu()
{
}

void ViewMenu::Draw()
{
	DrawTextAtMid("Raylib RTS Game!", { GameState::screenWidth / 2, 100 }, 36, BLACK);
	ViewBase::Draw();
}

ViewEnd::ViewEnd(std::string message, Color color)
{
	_message = message;
	_color = color;
}

void ViewEnd::Draw()
{
	DrawTextAtMid(_message.c_str(), { GameState::screenWidth / 2,  GameState::screenHeight / 2 }, 72, _color);
	ViewBase::Draw();
}
