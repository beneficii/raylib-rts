#pragma once

#include <memory>
#include <string>
#include "raylib.h"

class UnitData;
class UnitBehaviour;

enum class Faction
{
    Blue,   // Ally
    Red     // Enemy
};

namespace faction {
    Faction Oponent(Faction faction);
}

class Unit : public std::enable_shared_from_this<Unit>
{
public:

    Unit(UnitData* data, Faction faction, Vector2 position);

    ~Unit();

    void SetBehaviour(UnitBehaviour* object);

    // reset behaviour to default one
    void SetIddle();

    void Damage(int value);

    Vector2 AboveHead();

    void Draw();

    void Update();

    bool MoveTowards(Vector2 target);

    int health;
    int maxHealth;
    Faction faction;

    UnitData* data;

    std::string tag;

    std::string defaultBehaviour;

    Vector2 position;
    float extraScale;

private:
    float AnimationScale();

    Texture2D _texture;
    bool _isDead;
    UnitBehaviour* _behaviour;
    double _lastDamageTime;
    double _spawnTime;
};

