#include "UnitBehaviour.h"

#include "raylib.h"
#include "raymath.h"
#include "world/Unit.h"
#include "data/GameData.h"
#include "world/Bullet.h"
#include "Managers/GameState.h"
#include "helpers/draw.h"
#include <Constants.h>
#include <helpers/StringHelpers.h>
#include <ui/FloatingText.h>


UnitBehaviour::UnitBehaviour()
{
}

UnitBehaviour::~UnitBehaviour()
{

}



UnitBehaviour* UnitBehaviour::Create(std::string input)
{
    int idx = input.find(' ');
    std::string id = input.substr(0, idx);
    std::string data = input.substr(idx+1, input.length() - idx - 1);
    //std::cout << id << ":" << data << std::endl;

    switch (MyStrings::SHash(id.c_str()))
    {
    case MyStrings::SHash("find_target"): return new unitbehaviour::FindTarget();
    case MyStrings::SHash("find_resource"): return new unitbehaviour::FindResource(data);
    case MyStrings::SHash("generate"): return new unitbehaviour::GenerateResource(data);
    default: return new unitbehaviour::Iddle();
    }
}

void UnitBehaviour::Draw(std::shared_ptr<Unit> unit)
{
}

void UnitBehaviour::Update(std::shared_ptr<Unit> unit)
{
}

// behaviours

void unitbehaviour::Test::Update(std::shared_ptr<Unit> unit)
{
	if (unit->MoveTowards({ 300, 300 })) {
		unit->Damage(100);
	}
}

void unitbehaviour::Iddle::Update(std::shared_ptr<Unit> unit)
{
	// nothing
}

unitbehaviour::Attack::Attack(std::shared_ptr<Unit> target)
{
	this->target = target;
}

void unitbehaviour::Attack::Update(std::shared_ptr<Unit> unit)
{
    // if target died, we go back to iddle
    if (target.expired()) {
        unit->SetIddle();
        return;
    }

    // should run on the first update
    if (!cooldown.created)
    {
        cooldown = CooldownComponent(unit->data->rate);
    }

    // if attack is off cooldown
    if (cooldown.Use())
    {
        auto bullet = new Bullet(unit->position, unit->data->damage, target);
    }
}

unitbehaviour::Follow::Follow(std::shared_ptr<Unit> target)
{
    this->target = target;
}

void unitbehaviour::Follow::Update(std::shared_ptr<Unit> unit)
{
    if (target.expired()) {
        unit->SetIddle();
        return;
    }

    auto targetPtr = target.lock();


    if (Vector2Distance(unit->position, targetPtr->position) <= unit->data->Range())
    {
        unit->SetBehaviour(new Attack(targetPtr));
        return;
    }

    unit->MoveTowards(targetPtr->position);
}

unitbehaviour::FindTarget::FindTarget()
{
    // give it time to breathe
    cooldown = CooldownComponent(0.2f);
}

void unitbehaviour::FindTarget::TryFindTarget(std::shared_ptr<Unit> unit)
{
    bool canMove = unit->data->CanMove() && unit->tag != "guard";

    // if unit can't move then only search units in range
    float maxDistance = canMove ? FLT_MAX : unit->data->Range();

    auto target = GameState::GetInstance()->GetClosestUnit(unit->position, faction::Oponent(unit->faction), maxDistance);

    if (target != nullptr)
    {
        if (canMove)
        {
            unit->SetBehaviour(new Follow(target));
        }
        else
        {
            unit->SetBehaviour(new Attack(target));
        }
    }
}

void unitbehaviour::FindTarget::Update(std::shared_ptr<Unit> unit)
{
    // if we don't find target, we search again after short delay
    if (cooldown.Use())
    {
        TryFindTarget(unit);
    }
}

unitbehaviour::GenerateResource::GenerateResource(std::string resource)
{
    this->resource = resource;
}

void unitbehaviour::GenerateResource::Update(std::shared_ptr<Unit> unit)
{
    // should run on the first update
    if (!cooldown.created)
    {
        cooldown = CooldownComponent(unit->data->rate);
    }

    if (cooldown.Use())
    {
        auto msg = GameState::GetInstance()->Earn(resource, unit->data->damage);

        new FloatingText(unit->AboveHead(), msg, ResourceColor(resource));
    }
}


unitbehaviour::FindResource::FindResource(std::string resource)
{
    this->resource = resource;
    cooldown = CooldownComponent(0.25f);
    hasTarget = false;
    hasResource = false;
    target = { };
    _textureResource = GameState::GetInstance()->images[resource];
}

void unitbehaviour::FindResource::Draw(std::shared_ptr<Unit> unit)
{
    // draw a resource above a unit if they have it now
    if (hasResource) {
        DrawTextureAtMid(_textureResource, unit->AboveHead(), 1, WHITE);
    }
}

void unitbehaviour::FindResource::TryFindTarget(std::shared_ptr<Unit> unit)
{
    auto game = GameState::GetInstance();

    if (game->castle.expired()) return;

    auto castle = game->castle.lock();

    if (hasResource)
    {
        // bring resource back to castle
        target = castle->position;
    }
    else {
        // go get a resource
        target = (resource == "gold") ? game->mineGold->position : game->mineMana->position;
    }

    hasTarget = true;
}

void unitbehaviour::FindResource::Update(std::shared_ptr<Unit> unit)
{
    if (!hasTarget) {
        if (cooldown.Use()) {
            TryFindTarget(unit);
        }
        return;
    }

    if (Vector2Distance(unit->position, target) <= unit->data->Range())
    {
        if (hasResource) {
            // bring in the resource
            auto msg = GameState::GetInstance()->Earn(resource, unit->data->damage);
            hasResource = false;
            hasTarget = false;

            new FloatingText(unit->AboveHead(), msg, ResourceColor(resource));
        }
        else {
            // grab the resource
            hasResource = true;
            hasTarget = false;
        }
        return;
    }

    // else keep going
    unit->MoveTowards(target);
}
