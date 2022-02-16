#pragma once
#include "raylib.h"
#include "world/WorldObject.h"

class NeutralObject: public WorldObject
{
public:
	Vector2 position;
	Texture2D texture;

	NeutralObject(Vector2 position, Texture2D texture);
	~NeutralObject();

	void Update();
	void Draw();

private:

};
