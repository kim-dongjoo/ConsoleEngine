#include "Engine.h"
#include <iostream>

// ��������
// �ܼ� �Է� ó��(Ű����)
//


Engine::Engine()
{
}

Engine::~Engine()
{
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
			Update(deltaTime);
			Render();

			// �ð� ������Ʈ
			previousTime = currentTime;
		}
	}
}

void Engine::Quit()
{
	isQuit = true;
}

void Engine::ProcessInput()
{
	// ESC Ű ���� Ȯ��
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		Quit();
}

void Engine::Update(float deltaTime)
{
	std::cout
	<< "DeltaTime : " << deltaTime
	<< ", FPS : " << (1.0f/deltaTime)
	<< "\n";
}

void Engine::Render()
{
}
