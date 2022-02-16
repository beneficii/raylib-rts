#pragma once

class WorldObject
{
public:
	WorldObject();
	~WorldObject();

	void Destroy();

	virtual void Update() = 0;
	virtual void Draw() = 0;

private:

};


