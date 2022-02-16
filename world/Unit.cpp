#include "Unit.h"

#include "raymath.h"
#include "helpers/draw.h"
#include "data/GameData.h"
#include "Managers/GameState.h"
#include "data/UnitBehaviour.h"
#include "Constants.h"

Unit::Unit(UnitData* data, Faction faction, Vector2 position)
{
    this->data = data;
    this->faction = faction;
    this->position = position;
    this->extraScale = 1;

    this->health = this->maxHealth = data->hp;

    _texture = data->GetTexture();

    defaultBehaviour = data->behaviour;

    tag = data->tag;

    _isDead = false;
    _lastDamageTime = -10;
    _spawnTime = GetTime();

    _behaviour = nullptr;
    SetIddle();

    //ToDo: maybe animate spawn and play sound
}

Unit::~Unit()
{

}

void Unit::SetBehaviour(UnitBehaviour* object)
{
    // clean up old behaviour
    if (_behaviour != nullptr) {
        delete _behaviour;
    }

    _behaviour = object;
}

// reset behaviour to default one
void Unit::SetIddle()
{
    SetBehaviour(UnitBehaviour::Create(defaultBehaviour));
}

void Unit::Damage(int value)
{
    health -= value;
    if (health <= 0)
    {
        GameState::GetInstance()->RemoveUnit(shared_from_this());
    }

    _lastDamageTime = GetTime();
}

Vector2 Unit::AboveHead() {
    return { position.x, position.y - MyConst::tileSize * 0.45f };
}

// for now just minor scale effect at spawn
float Unit::AnimationScale()
{
    if (faction != Faction::Blue) return 1; // only animate allies

    float spawnTime = (GetTime() - _spawnTime)/0.35f;

    if (spawnTime >= 1) return 1;

    if (spawnTime < 0.8) return spawnTime * 1.4f / 0.8f;

    return 1.4f - (spawnTime-0.8f)*0.4f / 0.2f;
}

void Unit::Draw()
{
    // check if unit was recently damaged and show him in red if needed
    Color unitColor = GetTime() - _lastDamageTime > 0.15f ? WHITE: RED;

    //unit
    DrawTextureAtMid(_texture, position, MyConst::unitScale*extraScale * AnimationScale(), unitColor);

    // healthbar
    if (health < maxHealth) {
        float pixelsPerHp = 1;

        float width = pixelsPerHp * health;
        float height = 3;

        // draw health bar frame with 1 pixel border
        auto rect = Rectangle{
            position.x - width * 0.5f - 1,
            position.y - MyConst::tileSize * 0.5f - 1,
            width + 2,
            height + 2
        };

        DrawRectangleRec(rect, DARKGRAY);

        // reduce the frame and draw health
        rect.x += 1;
        rect.y += 1;
        rect.width -= 2;
        rect.height -= 2;

        DrawRectangleRec(rect, RED);
    }

    _behaviour->Draw(shared_from_this());
}

void Unit::Update()
{
    _behaviour->Update(shared_from_this());
}

bool Unit::MoveTowards(Vector2 target)
{
    position = MoveTowardsV2(position, target, data->moveSpeed);

    return IsSame(position, target);
}

Faction faction::Oponent(Faction faction)
{
    return faction == Faction::Blue ? Faction::Red : Faction::Blue;
}
