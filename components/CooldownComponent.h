#pragma once
#include <time.h>

class CooldownComponent
{
public:

    bool created;

    CooldownComponent();

    CooldownComponent(double cooldown);
    CooldownComponent(float cooldown);

    bool CanUse();

    bool Use();

private:
    double _next;
    double _cooldown;

    void SetNext();
};
