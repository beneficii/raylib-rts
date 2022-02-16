#pragma once

#include<string>
enum class Faction;

class SpellBehaviour
{
public:
	virtual void Execute(Faction faction) = 0;

	static void Cast(std::string input, Faction faction);
};

namespace spells
{
    class Nothing : public SpellBehaviour
    {
    public:
        void Execute(Faction faction);
    };

    class Charge : public SpellBehaviour
    {
    public:
        void Execute(Faction faction);
    };

    class AddResource : public SpellBehaviour
    {
    public:
        AddResource(std::string input);
        void Execute(Faction faction);
        
    private:
        std::string _resource;
        int _amount;
    };
}

