#pragma once

#include "Core.h"
#include <vector>
#include "RTTI.h"

class Actor;

class Engine_API Level : public RTTI
{
	RTTI_DECLARATIONS(Level, RTTI)

public:
	Level();
	~Level();

	void SpawnActor(Actor* newActor);

	// ���� �̺�Ʈ �Լ�
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

private:
	void SortActorsByRenderSortingOrder();

private:
	std::vector<Actor*> actors;


};

