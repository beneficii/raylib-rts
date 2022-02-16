#include "CooldownComponent.h"
#include "Managers/GameState.h"

CooldownComponent::CooldownComponent()
{
    _cooldown = 0;
    _next = 0;
    created = false;
}

CooldownComponent::CooldownComponent(double cooldown)
{
    _cooldown = cooldown;
    created = true;
    SetNext();
}

CooldownComponent::CooldownComponent(float cooldown) : CooldownComponent((double)cooldown) {}

bool CooldownComponent::CanUse()
{
    return created && GetTime() >= _next;
}

bool CooldownComponent::Use()
{
    if (CanUse())
    {
        SetNext();
        return true;
    }

    return false;
}

void CooldownComponent::SetNext()
{
    _next = GetTime() + _cooldown;
}