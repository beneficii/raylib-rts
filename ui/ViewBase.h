#pragma once

#include "raylib.h"
#include "Button.h"
#include <vector>

class ViewBase
{
public:
	std::vector<Button*> buttons;

	ViewBase();
	~ViewBase();

	virtual void Update();
	virtual void Draw();
	void CheckPress(Vector2 mousePos);

private:

};

