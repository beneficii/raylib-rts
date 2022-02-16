#pragma once
#include <string>
#include <memory>

#include "raylib.h"
#include "raymath.h"
#include "components/CooldownComponent.h"

class Unit;

class UnitBehaviour
{
public:
	UnitBehaviour();
	~UnitBehaviour();

	static UnitBehaviour* Create(std::string input);

    virtual void Update(std::shared_ptr<Unit> unit) = 0;
    virtual void Draw(std::shared_ptr<Unit> unit);

private:

};

namespace unitbehaviour
{
	class Test : public UnitBehaviour
	{
	public:
		void Update(std::shared_ptr<Unit> unit);
	};

    class Iddle : public UnitBehaviour
    {
    public:
        void Update(std::shared_ptr<Unit> unit);
    };

    class Attack : public UnitBehaviour
    {
    public:
        CooldownComponent cooldown;
        std::weak_ptr<Unit> target;

        Attack(std::shared_ptr<Unit> target);

        void Update(std::shared_ptr<Unit> unit);
    };


    class Follow : public UnitBehaviour
    {
    public:
        std::weak_ptr<Unit> target;

        Follow(std::shared_ptr<Unit> target);

        void Update(std::shared_ptr<Unit> unit);
    };

    class FindTarget : public UnitBehaviour
    {
    public:
        CooldownComponent cooldown;

        FindTarget();

        void TryFindTarget(std::shared_ptr<Unit> unit);

        void Update(std::shared_ptr<Unit> unit);
    };

    // basically like attack, but generate resources instead of damage
    class GenerateResource : public UnitBehaviour
    {
    public:
        CooldownComponent cooldown;
        std::string resource;

        GenerateResource(std::string resource);

        void Update(std::shared_ptr<Unit> unit);
    };

    class FindResource : public UnitBehaviour
    {
    public:
        CooldownComponent cooldown;
        std::string resource;

        bool hasTarget;
        Vector2 target;
        bool hasResource;

        FindResource(std::string resource);

        void TryFindTarget(std::shared_ptr<Unit> unit);

        void Update(std::shared_ptr<Unit> unit);
        virtual void Draw(std::shared_ptr<Unit> unit) override;

    private:
        Texture2D _textureResource;
    };
}