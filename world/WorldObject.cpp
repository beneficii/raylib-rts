#include "WorldObject.h"

#include "Managers/GameState.h"

WorldObject::WorldObject()
{
	GameState::GetInstance()->AddWorldObject(this);
}

WorldObject::~WorldObject()
{
}

void WorldObject::Destroy()
{
	GameState::GetInstance()->RemoveWorldObject(this);
}
