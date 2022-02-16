#pragma once

#include "raylib.h"
#include "Button.h"
#include "ItemButton.h"
#include "ViewBase.h"

class ViewPlay : public ViewBase
{
public:
	ViewPlay();
	~ViewPlay();

	void Update() override;
	void Draw() override;

private:
	

};
