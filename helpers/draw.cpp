#include "raylib.h"
#include "raymath.h"
#include <time.h>
#include <stdlib.h>
#include "draw.h"
#include <Constants.h>
#include <helpers/StringHelpers.h>

#define BLOCK_SIZE 10

void DrawBlock(Vector2 pos, Color color)
{
    DrawRectangle(pos.x, pos.y, BLOCK_SIZE - 1, BLOCK_SIZE - 1, color);
}

bool IsSame(Vector2 a, Vector2 b)
{
    return a.x == b.x && a.y == b.y;
}

Vector2 RandomPos(int maxWidth, int maxHeight)
{
    Vector2 pos;
    pos.x = (rand() % (maxWidth / BLOCK_SIZE)) * BLOCK_SIZE;
    pos.y = (rand() % (maxHeight / BLOCK_SIZE)) * BLOCK_SIZE;
    return pos;
}

void DrawTextAtMid(const char* text, Vector2 position, int fontSize, Color color)
{
    int textWidth = MeasureText(text, fontSize);

    DrawText(text, position.x - textWidth / 2, position.y - fontSize / 2, fontSize, color);
}

// Draw a Texture2D with extended parameters
void DrawTextureAtRect(Texture2D texture, Rectangle dest, Color tint)
{
    Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Vector2 origin = { 0.0f, 0.0f };

    DrawTexturePro(texture, source, dest, origin, 0, tint);
}

void DrawTextureAtMid(Texture2D texture, Vector2 position, float scale, Color tint)
{
    float width = (float)texture.width * scale;
    float height = (float)texture.height * scale;

    Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Rectangle dest = {
        position.x - width*0.5f,
        position.y - height * 0.5f, (float)texture.width * scale, (float)texture.height * scale };


    DrawTexturePro(texture, source, dest, Vector2{0,0}, 0, tint);
}

void DrawTextureAtMid(Texture2D texture, Vector2 position, Vector2 scale, Color tint)
{
    float width = (float)texture.width * scale.x;
    float height = (float)texture.height * scale.y;

    Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Rectangle dest = {
        position.x - width * 0.5f,
        position.y - height * 0.5f, (float)texture.width * scale.x, (float)texture.height * scale.y };


    DrawTexturePro(texture, source, dest, Vector2{ 0,0 }, 0, tint);
}

Vector2 MoveTowardsV2(Vector2 position, Vector2 target, float speed)
{
    return Vector2MoveTowards(position, target, speed * GetFrameTime() * MyConst::tileSize);
}

Color ResourceColor(std::string resource)
{
    switch (MyStrings::SHash(resource.c_str()))
    {
    case MyStrings::SHash("gold"): return GOLD;
    case MyStrings::SHash("mana"): return BLUE;
    case MyStrings::SHash("people"): return DARKGRAY;
    default:
        break;
    }
}
