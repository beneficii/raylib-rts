#pragma once

#include "raylib.h"
#include "Button.h"
#include "ViewBase.h"

class ViewMenu : public ViewBase
{
public:
	ViewMenu();
	~ViewMenu();

	void Draw() override;

private:

};

class ViewEnd : public ViewBase
{
public:
	ViewEnd(std::string message, Color color);

	void Draw() override;

private:
	std::string _message;
	Color _color;

};

// this is for button
void MenuPlay();
