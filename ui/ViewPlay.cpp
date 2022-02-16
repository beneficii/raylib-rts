#include "ViewPlay.h"

#include "helpers/draw.h"
#include <iostream>
#include <sstream>
#include "Managers/GameState.h"
#include <Constants.h>


ViewPlay::ViewPlay()
{
	GameState* game = GameState::GetInstance();

	float spacing = 90;

	buttons.push_back(new ItemButton(game->units.at("worker"), { 40, spacing }, 4, Faction::Blue));
	buttons.push_back(new ItemButton(game->units.at("mage"), { 40, spacing*2 }, 4, Faction::Blue));
	buttons.push_back(new ItemButton(game->units.at("warrior1"), { 40, spacing*3 }, 4, Faction::Blue));
	buttons.push_back(new ItemButton(game->units.at("tower"), { 40, spacing*4 }, 4, Faction::Blue));
	buttons.push_back(new ItemButton(game->spells.at("populate"), { 40, spacing * 5 }, 4, Faction::Blue));

	if (MyConst::CHEAT_ENABLED) {
		buttons.push_back(new ItemButton(game->spells.at("charge"), { 40, spacing * 6 }, 4, Faction::Blue));

		buttons.push_back(new ItemButton(game->units.at("worker"), { 920, spacing }, 4, Faction::Red));
		buttons.push_back(new ItemButton(game->units.at("mage"), { 920, spacing * 2 }, 4, Faction::Red));
		buttons.push_back(new ItemButton(game->units.at("warrior1"), { 920, spacing * 3 }, 4, Faction::Red));
		buttons.push_back(new ItemButton(game->units.at("tower"), { 920, spacing * 4 }, 4, Faction::Red));
		buttons.push_back(new ItemButton(game->spells.at("populate"), { 920, spacing * 5 }, 4, Faction::Red));
		buttons.push_back(new ItemButton(game->spells.at("charge"), { 920, spacing * 6 }, 4, Faction::Red));
	}

	game->InitPlay();
}

ViewPlay::~ViewPlay()
{
}

void ViewPlay::Update()
{
	// not the best solution, but it works
	GameState::GetInstance()->PlayUpdate();
}

void ViewPlay::Draw()
{

	GameState* game = GameState::GetInstance();

	game->PlayDraw();

	std::stringstream resourceLine;
	resourceLine 
		<< game->resources.at("gold") << "g" << "\t"
		<< game->resources.at("mana") << "m" << "\t"
		<< game->resources.at("people") << "p" << "\t";

	DrawTextAtMid(
		resourceLine.str().c_str(),
		{ GameState::screenWidth / 2, 20},
		20,
		BLACK);

	DrawTextAtMid(
		("Time: " + std::to_string(65 - (int)game->PlayTime())).c_str(),
		{ GameState::screenWidth / 2+300, 20 },
		20,
		BLACK);

	ViewBase::Draw();

	DrawFPS(200, 20);
}