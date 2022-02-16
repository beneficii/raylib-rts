#include "GameData.h"

#include <memory>
#include <sstream>
#include "Managers/GameState.h"
#include "world/Unit.h"
#include <Constants.h>
#include <helpers/StringHelpers.h>
#include <data/SpellBehaviour.h>


inline std::string ItemData::CostText()
{
    return std::to_string(price) + resource[0];  // first character of resource name is his shorthand name
}

inline bool ItemData::EnoughResources()
{
    return GameState::GetInstance()->EnoughResources(resource, price);
}

void ItemData::Pay()
{
    GameState::GetInstance()->Pay(resource, price);
}

void ItemData::Action(Faction faction)
{
    std::cout << "Perform: " << name << std::endl;
}

Texture2D ItemData::GetTexture()
{
    return GameState::GetInstance()->images.at(sprite);
}

inline bool UnitData::CanMove()
{
    return moveSpeed > 0;
}

inline std::string UnitData::CostText()
{
    // units cost 1 people in addition to their base cost
    return ItemData::CostText() + " " + "1p";
}

inline bool UnitData::EnoughResources()
{
    if (!ItemData::EnoughResources()) return false;

    // units cost 1 people in addition to their base cost
    if (!GameState::GetInstance()->EnoughResources("people", 1)) return false;

    return true;
}

void UnitData::Pay()
{
    ItemData::Pay();

    GameState::GetInstance()->Pay("people", 1);
}

void UnitData::Action(Faction faction)
{
    GameState::GetInstance()->AddUnit(std::make_shared<Unit>(
        this,
        faction,
        GameState::GetInstance()->GetSpawnSpot(faction, CanMove())));
}

float UnitData::Range()
{
    return range * MyConst::tileSize;
}

UnitData* UnitData::FromCSV(std::string line)
{
    UnitData* data = new UnitData();

    std::istringstream stream(line);

    // csv structure
    // id	name	description	damage	rate	range	hp	moveSpeed	price	resource	behaviour	tag	sprite
    data->id = MyStrings::GetString(&stream);

    if (data->id.empty()) {
        delete data;
        return nullptr;
    }

    data->name = MyStrings::GetString(&stream);
    data->description = MyStrings::GetString(&stream);
    data->damage = MyStrings::GetInt(&stream);
    data->rate = MyStrings::GetFloat(&stream);
    data->range = MyStrings::GetFloat(&stream);
    data->hp = MyStrings::GetInt(&stream);
    data->moveSpeed = MyStrings::GetFloat(&stream);
    data->price = MyStrings::GetInt(&stream);
    data->resource = MyStrings::GetString(&stream);
    data->behaviour = MyStrings::GetString(&stream);
    data->tag = MyStrings::GetString(&stream);
    data->sprite = MyStrings::GetString(&stream);

    return data;
}

void SpellData::Action(Faction faction)
{
    SpellBehaviour::Cast(action, faction);
}

SpellData* SpellData::FromCSV(std::string line)
{
    SpellData* data = new SpellData();

    std::istringstream stream(line);

    // csv structure
    // id	name	description	sprite	price	resource	action
    data->id = MyStrings::GetString(&stream);
    if (data->id.empty()) {
        delete data;
        return nullptr;
    }

    data->name = MyStrings::GetString(&stream);
    data->description = MyStrings::GetString(&stream);
    data->sprite = MyStrings::GetString(&stream);
    data->price = MyStrings::GetInt(&stream);
    data->resource = MyStrings::GetString(&stream);
    data->action = MyStrings::GetString(&stream);

    return data;
}

ScenarioData ScenarioData::FromCSV(std::string line)
{
    ScenarioData data;

    std::istringstream stream(line);

    // csv structure
    // time	text	spell	summon
    data.time = MyStrings::GetFloat(&stream);
    data.text = MyStrings::GetString(&stream);
    data.spell = MyStrings::GetStringList(&stream);
    data.summon = MyStrings::GetStringList(&stream);

    return data;
}
