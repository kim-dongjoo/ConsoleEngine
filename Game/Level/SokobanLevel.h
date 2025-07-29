#pragma once

#include "Level/Level.h"
#include "Interface//ICanPlayerMove.h"

class SokobanLevel : public Level, public ICanPlayerMove
{
	RTTI_DECLARATIONS(SokobanLevel, Level)

public:
	SokobanLevel();

	virtual void Render() override;

	// ICanPlayerMove��(��) ���� ��ӵ�
	virtual bool CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition) override;

private:
	void ReadMapFile(const char* filename);

	//  ���� Ŭ���� Ȯ���ϴ� �Լ�
	bool CheckGameClear();

private:
	// ���� Ŭ��� ���� ����
	int targetScore = 0;

	// ���� Ŭ���� ���� Ȯ�� ����
	bool isGameClear = false;
};