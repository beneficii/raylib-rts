#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "raylib.h"

enum class Faction;

struct ItemData
{
    std::string id;

    std::string name;
    
    std::string description;

    int price;
    std::string resource;

    std::string sprite;

    virtual std::string CostText();

    virtual bool EnoughResources();
    virtual void Pay();

    virtual void Action(Faction faction);

    virtual Texture2D GetTexture();
};

struct UnitData : ItemData
{
    bool CanMove();

    int damage;
    float rate;
    float range;

    int hp;

    float moveSpeed;

    std::string behaviour;
    std::string tag;

    std::string CostText() override;

    bool EnoughResources() override;
    void Pay() override;

    void Action(Faction faction) override;

    float Range();

    static UnitData* FromCSV(std::string line);
};

struct SpellData : ItemData
{
    std::string action;

    void Action(Faction faction) override;

    static SpellData* FromCSV(std::string line);
};

struct ScenarioData
{
    float time;
    std::string text;
    std::vector<std::string> spell;
    std::vector<std::string> summon;

    static ScenarioData FromCSV(std::string line);
};
