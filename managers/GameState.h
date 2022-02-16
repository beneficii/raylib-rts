#pragma once

#include "raylib.h"
#include "ui/ViewBase.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "data/GameData.h"
#include <queue>
#include "world/Unit.h"
#include "world/NeutralObject.h"
#include <memory>

class WorldObject;

class GameState
{
protected:
    inline static GameState* _current = nullptr;

public:
    static const int screenWidth = 960;
    static const int screenHeight = 540;

    std::unordered_map<std::string, Texture2D> images;
    std::unordered_map<std::string, int> resources;
    std::unordered_map<std::string, UnitData*> units;
    std::unordered_map<std::string, SpellData*> spells;
    std::queue<ScenarioData> scenario;

    std::unordered_set<std::shared_ptr<Unit>> blueUnits;
    std::unordered_set<std::shared_ptr<Unit>> redUnits;
    std::vector<std::shared_ptr<Unit>> unitsToCreate;
    std::vector<std::shared_ptr<Unit>> unitsToDelete;

    std::unordered_set<WorldObject*> objects;
    std::vector<WorldObject*> objectsToCreate;
    std::vector<WorldObject*> objectsToDelete;

    // static objects
    NeutralObject* mineGold;
    NeutralObject* mineMana;
    std::weak_ptr<Unit> castle;
    std::weak_ptr<Unit> king;

	GameState();
	~GameState();

    void FirstInit();
    void InitPlay();

    void InitResources();
    void InitUnits();
    void InitSpells();
    void InitScenario();

    bool EnoughResources(std::string type, int amount);

    void Pay(std::string type, int amount);

    std::string Earn(std::string type, int amount);

    void LoadImages();

    void UnLoadImages();

    double PlayTime();

    void UpdateScenario();

    void Update();
    void PlayUpdate();

    void Draw();
    void PlayDraw();

    void SetView(ViewBase* view);

    std::unordered_set<std::shared_ptr<Unit>>* GetArmy(Faction faction);

    Vector2 GetSpawnSpot(Faction faction, bool isMoving);
    std::shared_ptr<Unit> GetClosestUnit(Vector2 origin, Faction faction, float maxDistance);

    void AddUnit(std::shared_ptr<Unit> unit);
    void RemoveUnit(std::shared_ptr<Unit> unit);

    void AddWorldObject(WorldObject* obj);
    void RemoveWorldObject(WorldObject* obj);

    // Singletons should not be cloneable.
    GameState(GameState& other) = delete;

    // Singletons should not be assignable.
    void operator=(const GameState&) = delete;

    static GameState* GetInstance();

private:
    ViewBase* _view;
    time_t _startTime;
};