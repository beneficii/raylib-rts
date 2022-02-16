#include "NeutralObject.h"
#include <helpers/draw.h>

NeutralObject::NeutralObject(Vector2 position, Texture2D texture)
{
	this->position = position;
	this->texture = texture;
}

NeutralObject::~NeutralObject()
{
}

void NeutralObject::Update()
{
	// nothing
}

void NeutralObject::Draw()
{
	DrawTextureAtMid(texture, position, 2, WHITE);
}
