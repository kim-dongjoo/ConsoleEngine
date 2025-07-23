#include "Engine.h"
#include <iostream>
#include "../Level//Level.h"

// ��������
// �ܼ� �Է� ó��(Ű����)
//


Engine::Engine()
{
}

Engine::~Engine()
{
	if (mainLevel)
	{
		delete mainLevel;
	}
}

void Engine::Run()
{
	LARGE_INTEGER currentTime;
	LARGE_INTEGER previousTime;

	QueryPerformanceCounter(&currentTime);
	previousTime = currentTime;

	// �ϵ���� �ð��� ���ļ� ��������
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	// Ÿ�� ������ ����Ʈ
	float targetFrameRate = 60.0f;

	// Ÿ�� �� ������ ����
	float oneFrameTime = 1.0f / targetFrameRate;

	// GameLoop
	while (true)
	{
		// ���� ���� ���� Ȯ��
		if (isQuit)
			break;

		// ������ �ð� ���
		// (���� �ð� - ���� �ð�) / ���ļ�
		QueryPerformanceCounter(&currentTime);

		// ������ �ð�
		float deltaTime = (currentTime.QuadPart - previousTime.QuadPart) / (float)frequency.QuadPart;
		QueryPerformanceCounter(&currentTime);

		ProcessInput();

		// ������ 60 ���Ϸ� ����
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// �ð� ������Ʈ
			previousTime = currentTime;

			// ���� �������� �Է��� ���
			for (int idx = 0; idx < 255; ++idx)
			{
				keyStates[idx].previousKeyDown = keyStates[idx].isKeyDown;
			}
		}
	}
}

void Engine::AddLevel(Level* newLevel)
{
	if (mainLevel)
	{
		delete mainLevel;
	}

	mainLevel = newLevel;
}

bool Engine::GetKey(int keyCode)
{
	return keyStates[keyCode].isKeyDown;
}

bool Engine::GetKeyDown(int keyCode)
{
	return keyStates[keyCode].isKeyDown && !keyStates[keyCode].previousKeyDown;
}

bool Engine::GetKeyUp(int keyCode)
{
	return !keyStates[keyCode].isKeyDown && keyStates[keyCode].previousKeyDown;
}

void Engine::Quit()
{
	isQuit = true;
}

void Engine::ProcessInput()
{
	// Ű �Է� Ȯ��
	for (int idx = 0; idx < 255; ++idx)
	{
		keyStates[idx].isKeyDown = GetAsyncKeyState(idx) & 0x8000;
	}

	// ESC Ű ���� Ȯ��
	// if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	//	Quit();
}

void Engine::BeginPlay()
{
	if (mainLevel)
	{
		mainLevel->BeginPlay();
	}
}

void Engine::Tick(float deltaTime)
{
	//std::cout
	//<< "DeltaTime : " << deltaTime
	//<< ", FPS : " << (1.0f/deltaTime)
	//<< "\n";

	// ���� ������Ʈ
	if (mainLevel)
	{
		mainLevel->Tick(deltaTime);
	}

	if (GetKeyDown(VK_ESCAPE)) { Quit(); }
}

void Engine::Render()
{
	if (mainLevel)
	{
		mainLevel->Render();
	}
}
