#pragma once
#include "Button.h"
#include "data/GameData.h"

class ItemButton : public Button
{
public:
	ItemButton(ItemData* data, Vector2 position, float scale, Faction faction);
	~ItemButton();

	void Draw() override;
	bool TryPress(Vector2 mousePoint) override;

private:
	ItemData* _data;
	Texture2D _imgUnlocked;
	Texture2D _imgLocked;
	Texture2D _imgIcon;

	bool _unlocked;
	Faction _faction;
	std::string _cachedCost;

};
