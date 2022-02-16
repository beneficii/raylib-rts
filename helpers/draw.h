#pragma once

#include <string>

void DrawBlock(Vector2 pos, Color color);

bool IsSame(Vector2 a, Vector2 b);

Vector2 RandomPos(int maxWidth, int maxHeight);

void DrawTextAtMid(const char* text, Vector2 position, int fontSize, Color color);

void DrawTextureAtRect(Texture2D texture, Rectangle dest, Color tint);

void DrawTextureAtMid(Texture2D texture, Vector2 position, float scale, Color tint);

Vector2 MoveTowardsV2(Vector2 position, Vector2 target, float speed);

Color ResourceColor(std::string resource);