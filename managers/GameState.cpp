#include "GameState.h"
#include <iostream>
#include <filesystem>
#include "ui/ViewMenu.h"
#include <time.h>
#include <fstream>
#include "world/Unit.h"
#include "world/WorldObject.h"
#include <limits>
#include "raymath.h"
#include <helpers/StringHelpers.h>
#include <Constants.h>
#include <ui/FloatingText.h>

using namespace std;

GameState::GameState()
{
	InitResources();
	LoadImages();
	InitUnits();
	InitSpells();
	InitScenario();

	time_t _startTime = time(0);
}

void GameState::FirstInit()
{
	_view = new ViewMenu();
}

void GameState::InitPlay()
{
	// put castle and mines
	auto castle = make_shared<Unit>(units["castle"], Faction::Blue, Vector2{ 480, 500 });
	AddUnit(castle);
	this->castle = castle;
	float resourceOffset = 90;
	mineGold = new NeutralObject(Vector2{ 480 - resourceOffset, 500 }, images["mine_gold"]);
	mineMana = new NeutralObject(Vector2{ 480 + resourceOffset, 500 }, images["mine_mana"]);

	auto king = make_shared<Unit>(units["boss"], Faction::Red, Vector2{ 480, 60 });
	AddUnit(king);
	this->king = king;
	king->extraScale = 2;

	_startTime = GetTime();
}

GameState::~GameState()
{
	UnLoadImages();
	delete _view;

	// clear units
	for (auto& it : units) {
		delete it.second;
	}

	// clear spells
	for (auto& it : spells) {
		delete it.second;
	}

	// clear spells
	for (auto& it : objects) {
		delete it;
	}
}

// Load units data from csv file
void GameState::InitUnits()
{
	fstream csvFile;
	csvFile.open("resources/csv/units.csv", ios::in);

	string line;
	getline(csvFile, line);				//skip header line
	while (getline(csvFile, line))
	{
		UnitData* data = UnitData::FromCSV(line);
		if (data == nullptr) continue;

		units[data->id] = data;
	}
}

// Load spells data from csv file
void GameState::InitSpells()
{
	fstream csvFile;
	csvFile.open("resources/csv/spells.csv", ios::in);

	string line;
	getline(csvFile, line);				//skip header line
	while (getline(csvFile, line))
	{
		SpellData* data = SpellData::FromCSV(line);
		if (data == nullptr) continue;

		spells[data->id] = data;
	}
}

// Load scenario entries from csv file
void GameState::InitScenario()
{
	fstream csvFile;
	csvFile.open("resources/csv/scenario.csv", ios::in);

	string line;
	getline(csvFile, line);				//skip header line
	while (getline(csvFile, line))
	{
		ScenarioData data = ScenarioData::FromCSV(line);
		scenario.push(data);
	}
}

void GameState::InitResources()
{
	// init each resource to its starting value
	resources["gold"] = 25;
	resources["mana"] = 0;
	resources["people"] = 3;
}

bool GameState::EnoughResources(string type, int amount)
{
	return resources.at(type) >= amount;
}

void GameState::Pay(string type, int amount)
{
	resources[type] -= amount;
}

// returns string of resources earned
string GameState::Earn(string type, int amount)
{
	resources[type] += amount;

	string msg = "+";
	msg += to_string(amount);
	msg += type.substr(0,1);


	return msg;
}


// iterate image folder and load each into unordered map by their name
void GameState::LoadImages()
{
	std::string path = "resources/img/";
	for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
		if (entry.path().extension() != ".png") continue;

		string filename = entry.path().filename().string();

		size_t dotIndex = filename.find_last_of(".");
		filename = filename.substr(0, dotIndex);

		//std::cout << filename << std::endl;

		//preload all images into memory
		images.insert({
			filename,
			LoadTexture(entry.path().string().c_str())
		});
	}
}

void GameState::UnLoadImages()
{
	// clear images from memory
	for (auto& it : images) {
		UnloadTexture(it.second);
	}
}

double GameState::PlayTime()
{
	return GetTime() - _startTime;
}

void GameState::UpdateScenario()
{
	if (scenario.empty()) return;

	float playTime = PlayTime();

	auto& firstScenario = scenario.front();
	if (playTime >= firstScenario.time) {
		// clear spells
		for (auto& it : firstScenario.spell) {
			spells[it]->Action(Faction::Blue);
		}

		for (auto& it : firstScenario.summon) {
			units[it]->Action(Faction::Red);
		}

		if (!firstScenario.text.empty()) {
			new FloatingText(Vector2{480, 460}, firstScenario.text, RED, 20, 8, 1.2);
		}

		scenario.pop();
	}
}

GameState* GameState::GetInstance()
{
    if (_current == nullptr) {
        _current = new GameState();

		_current->FirstInit();
    }

    return _current;
}

void GameState::Update()
{
	_view->Update();

	// check inputs
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePoint = GetMousePosition();
		_view->CheckPress(mousePoint);
	}

	
	if (MyConst::CHEAT_ENABLED) {

		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			for (size_t i = 0; i < 10; i++)
			{
				Vector2 mousePoint = GetMousePosition();
				_view->CheckPress(mousePoint);
			}
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
			for (size_t i = 0; i < 1000; i++)
			{
				Vector2 mousePoint = GetMousePosition();
				_view->CheckPress(mousePoint);
			}
		}

		if (IsKeyPressed(KEY_T)) {
			Earn("gold", 999999);
			Earn("mana", 999999);
			Earn("people", 999999);
		}
	}
}

void GameState::PlayUpdate()
{
	// units
	for (const auto& unit : blueUnits) {
		unit->Update();
	}

	for (const auto& unit : redUnits) {
		unit->Update();
	}

	// world objects
	for (const auto& obj : objects) {
		obj->Update();
	}

	// create and destroy world objects
	for (const auto& obj : objectsToDelete) {
		objects.erase(obj);
		delete obj;
	}
	objectsToDelete.clear();

	for (const auto& obj : objectsToCreate) {
		objects.insert(obj);
	}
	objectsToCreate.clear();

	// create and destroy units
	for (const auto& unit : unitsToDelete) {
		auto army = GetArmy(unit->faction);

		army->erase(unit);
	}
	unitsToDelete.clear();

	for (const auto& unit : unitsToCreate) {
		auto army = GetArmy(unit->faction);
		army->insert(unit);
	}
	unitsToCreate.clear();

	UpdateScenario();
}

void GameState::Draw()
{
	// view
	_view->Draw();
}

void GameState::PlayDraw()
{
	// units
	for (const auto& unit : blueUnits) {
		unit->Draw();
	}

	for (const auto& unit : redUnits) {
		unit->Draw();
	}

	// world objects
	for (const auto& obj : objects) {
		obj->Draw();
	}
}

void GameState::SetView(ViewBase *view)
{
	delete _view; // we don't need old view anymore
	_view = view;
}

unordered_set<std::shared_ptr<Unit>>* GameState::GetArmy(Faction faction)
{
	switch (faction)
	{
	case Faction::Blue:
		return &blueUnits;
	case Faction::Red:
	default:
		return &redUnits;
	}
}

// random position for speciffic units to spawn
Vector2 GameState::GetSpawnSpot(Faction faction, bool isMoving)
{
	int yMin;
	int yMax;

	if (faction == Faction::Blue) {
		if (isMoving) {
			// ally unit
			yMin = 450;
			yMax = 500;
		}
		else {
			// ally tower
			yMin = yMax = 380;
		}
		
	}
	else {
		// enemy anything
		yMin = 90;
		yMax = 110;
	}

	float xMin = 480 - 80;
	float xMax = 480 + 80;

	float x = GetRandomValue(xMin, xMax);
	float y = GetRandomValue(yMin, yMax);

	return { x,y };
}

shared_ptr<Unit> GameState::GetClosestUnit(Vector2 origin, Faction faction, float maxDistance)
{
	auto army = GetArmy(faction);
	shared_ptr<Unit> closest(nullptr);
	float minDistance = maxDistance;
	
	for (const auto& unit : *army)
	{
		float distance = Vector2Distance(origin, unit->position);
		
		if (distance < minDistance) {
			minDistance = distance;
			closest = unit;
		}
	}

	return closest;
}

void GameState::AddUnit(shared_ptr<Unit> unit)
{
	unitsToCreate.push_back(unit);
}

void GameState::RemoveUnit(shared_ptr<Unit> unit)
{
	unitsToDelete.push_back(unit);

	// check ending condions

	switch (MyStrings::SHash(unit->data->id.c_str()))
	{
	case MyStrings::SHash("boss"):
		SetView(new ViewEnd("Victory!", DARKGREEN));
		break;
	case MyStrings::SHash("castle"):
		SetView(new ViewEnd("Defeat!", RED));
		break;
	default:
		break;
	}
}

void GameState::AddWorldObject(WorldObject* obj)
{
	objectsToCreate.push_back(obj);
}

void GameState::RemoveWorldObject(WorldObject* obj)
{
	objectsToDelete.push_back(obj);
}

