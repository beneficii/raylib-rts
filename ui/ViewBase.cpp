#include "ViewBase.h"

#include <iostream>

ViewBase::ViewBase()
{
}

ViewBase::~ViewBase()
{
	for (Button* it : buttons) {
		delete it;
	}
}

void ViewBase::Update()
{
}

void ViewBase::Draw()
{
	for (Button* it : buttons) {
		it->Draw();
	}
}

void ViewBase::CheckPress(Vector2 mousePos)
{
	for (Button* it : buttons) {
		it->TryPress(mousePos);
	}
}