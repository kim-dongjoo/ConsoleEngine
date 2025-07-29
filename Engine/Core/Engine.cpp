#include "Engine.h"
#include <iostream>
#include "Level/Level.h"
#include <Windows.h>
#include "Utils/Utils.h"

// ��������
// �ܼ� �Է� ó��(Ű����)
//

Engine* Engine::instance = nullptr;

BOOL WINAPI ConsoleMessageProcedure(DWORD CtrlType)
{
	switch (CtrlType)
	{
		case CTRL_CLOSE_EVENT:
		//Engine�� �޸� ����
		Engine::GetEngine().CleanUp();
		return false;


	}

	return false;

}

Engine::Engine()
{
	instance = this;

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 1;

	//�ܼ� Ŀ�� ����
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	// �ܼ� â �̺�Ʈ ���
	SetConsoleCtrlHandler(ConsoleMessageProcedure, TRUE);

}

Engine::~Engine()
{
	CleanUp();
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

		input.ProcessInput();

		// ������ 60 ���Ϸ� ����
		if (deltaTime >= oneFrameTime)
		{
			BeginPlay();
			Tick(deltaTime);
			Render();

			// �ð� ������Ʈ
			previousTime = currentTime;

			// ���� �������� �Է��� ���
			input.SavePreviousKeyStates();
		}
	}

	// �ؽ�Ʈ ���� �ٽ� ������� ����

	Utils::SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

}

void Engine::AddLevel(Level* newLevel)
{
	if (mainLevel)
	{
		delete mainLevel;
	}

	mainLevel = newLevel;
}

void Engine::CleanUp()
{
	// ���� ����
	SafeDelete(mainLevel);
}

void Engine::Quit()
{
	isQuit = true;
}

Engine& Engine::GetEngine()
{
	return *instance;
}

//void Engine::ProcessInput()
//{
//	// Ű �Է� Ȯ��
//	for (int idx = 0; idx < 255; ++idx)
//	{
//		keyStates[idx].isKeyDown = GetAsyncKeyState(idx) & 0x8000;
//	}
//
//	// ESC Ű ���� Ȯ��
//	// if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
//	//	Quit();
//}

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

	// if (GetKeyDown(VK_ESCAPE)) { Quit(); }
}

void Engine::Render()
{
	Utils::SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	/*SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
	);*/

	if (mainLevel)
	{
		mainLevel->Render();
	}
}
