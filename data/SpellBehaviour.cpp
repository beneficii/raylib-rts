#include "SpellBehaviour.h"

#include <world/Unit.h>
#include <Managers/GameState.h>
#include <sstream>
#include <helpers/StringHelpers.h>
#include <ui/FloatingText.h>
#include <helpers/draw.h>

SpellBehaviour* GetSpell(std::string input)
{
    int idx = input.find(' ');
    std::string id = input.substr(0, idx);
    std::string data = input.substr(idx + 1, input.length() - idx - 1);

    switch (MyStrings::SHash(id.c_str()))
    {
    case MyStrings::SHash("charge"): return new spells::Charge();
    case MyStrings::SHash("add"): return new spells::AddResource(data);
    default: return new spells::Nothing();
    }
}

void SpellBehaviour::Cast(std::string input, Faction faction)
{
    auto spell = GetSpell(input);
    spell->Execute(faction);

    delete spell;
}

void spells::Nothing::Execute(Faction faction)
{
	// nothing
    std::cout << "nothing was cast!" << std::endl;
}

void spells::Charge::Execute(Faction faction)
{
    auto army = GameState::GetInstance()->GetArmy(faction);
    for (auto& unit : *army) {
        if (unit->data->CanMove()) {
            if (unit->tag == "guard") unit->tag = "";
            // units that can move now actively search for target
            unit->defaultBehaviour = "find_target";
            unit->SetIddle();
        }
    }
}

spells::AddResource::AddResource(std::string input)
{
    std::istringstream stream(input);

    // example: 10 people
    _amount = MyStrings::GetInt(&stream, ' ');
    _resource = MyStrings::GetString(&stream, ' ');
}

void spells::AddResource::Execute(Faction faction)
{
    auto msg = GameState::GetInstance()->Earn(_resource, _amount);
    
    new FloatingText(Vector2{ 480, 460 }, msg, ResourceColor(_resource), 16, 16, 0.3);
}
