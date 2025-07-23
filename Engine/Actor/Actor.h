#pragma once

#include "Core.h"
#include "../Math/Vector2.h"

// ��ġ
// �׸���
// ������ �̺�Ʈ �Լ� ȣ��(BeginPlay/Tick/Draw)

class Engine_API Actor
{
public:
	Actor();
	virtual ~Actor();

	// �̺�Ʈ �Լ�
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	inline bool HasBeganPlay() const { return hasBeganPlay; }

private:
	Vector2 position;

	// �׸� ��
	char image = ' ';

	// BeginPlay�� ȣ�� �Ǿ����� Ȯ��
	bool hasBeganPlay = false;

};

