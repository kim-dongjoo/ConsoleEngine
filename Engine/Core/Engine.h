#pragma once

#include "Core.h"
#include <Windows.h>

/*
* TODO :  2025�� 7�� 24��
	- RTTI ����
	- Engine �̱���(Singleton) ����
* 
*/

class Level;

class Engine_API Engine
{
	struct KeyState
	{
		// ���� �����ӿ� Ű�� ���ȴ���
		bool isKeyDown = false;
		// ���� �����ӿ� Ű�� ���ȴ���
		bool previousKeyDown = false;
	};

public:
	// ������
	Engine();

	// �Ҹ���
	~Engine();

	// ���� ���� �Լ�
	void Run();

	// ���� �߰� �Լ�
	void AddLevel(Level* newLevel);

	// Ű Ȯ�� �Լ�
	bool GetKey(int keyCode);
	bool GetKeyDown(int keyCode);
	bool GetKeyUp(int keyCode);

	// ���� ���� �Լ�
	void Quit();

private:
	void ProcessInput();
	void BeginPlay();
	void Tick(float deltaTime = 0.0f);
	void Render();

private:
	// ���� ���� �÷���
	bool isQuit = false;

	// Ű �Է� ���� ���� ����
	KeyState keyStates[255];

	// ���� ����
	Level* mainLevel = nullptr;
};

