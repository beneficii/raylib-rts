#include "ItemButton.h"
#include "Managers/GameState.h"
#include "helpers/draw.h"
#include <iostream>
#include <ui/FloatingText.h>

using namespace std;

ItemButton::ItemButton(ItemData* data, Vector2 position, float scale, Faction faction)
	: Button("grass", "", position, scale, nullptr)
{
	_data = data;

	GameState* game = GameState::GetInstance();
	_imgLocked = game->images["frame_locked"];
	_imgUnlocked = game->images["frame_aviable"];
	_imgIcon = game->images[data->sprite];
	_faction = faction;

	_cachedCost = data->CostText();
}

ItemButton::~ItemButton()
{
}

inline void ItemButton::Draw()
{
	Button::Draw();
	
	GameState* game = GameState::GetInstance();

	_unlocked = _data->EnoughResources();
	//cout << _data->name<<"[" <<_data->price << _data->resource <<"]" << ": " << _unlocked << endl;

	//DrawTextureEx(_imgIcon, { _rect.x, _rect.y }, 0, _scale, WHITE); 
	DrawTextureAtRect(_imgIcon, { _rect.x, _rect.y, _rect.width, _rect.height }, WHITE); //portrait of unit or spell

	DrawTextureEx(_unlocked?_imgUnlocked:_imgLocked, { _rect.x, _rect.y }, 0, _scale, WHITE); // Draw button frame

	int fontSize = 7;
	DrawTextAtMid(_cachedCost.c_str(), { _rect.x + _rect.width/2, _rect.y + _rect.height + fontSize }, fontSize, BLACK);
}

bool ItemButton::TryPress(Vector2 mousePoint)
{
	if (!Button::TryPress(mousePoint)) return false;

	if (!_unlocked)
	{
		new FloatingText(Vector2{ 480, 460 }, "not enough resources", RED, 18, 20, 0.4);
		return false;
	}

	_data->Pay();

	// hardcode ally buttons only for now
	_data->Action(_faction);

	return true;
}
