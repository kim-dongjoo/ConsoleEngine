#pragma once

#include "Core.h"
#include "../Math/Vector2.h"
#include "RTTI.h"
#include <Windows.h>

// ��ġ
// �׸���
// ������ �̺�Ʈ �Լ� ȣ��(BeginPlay/Tick/Draw)

// ����
enum class Color : int
{
	Blue =	1,
	Green = 2,
	Red = 4,
	White = Red | Green | Blue,
	Intensity = 8
};

class Engine_API Actor : public RTTI
{
	RTTI_DECLARATIONS(Actor, RTTI)

public:
	Actor(const char image = ' ', Color color = Color::White);
	virtual ~Actor();

	// �̺�Ʈ �Լ�
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void Render();

	// BeginPlay ȣ�� ���� Ȯ��
	inline bool HasBeganPlay() const { return hasBeganPlay; }

	// ��ġ ����/�� �д� �Լ�
	void SetPosition(const Vector2& newPosition);
	Vector2 GetPosition() const;

private:
	Vector2 position;

	// �׸� ��
	char image = ' ';

	// ����
	Color color ;

	// BeginPlay�� ȣ�� �Ǿ����� Ȯ��
	bool hasBeganPlay = false;

};

