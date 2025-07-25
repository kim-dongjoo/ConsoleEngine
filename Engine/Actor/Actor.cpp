#include "Actor.h"
#include <Windows.h>
#include <iostream>

Actor::Actor(const char image, Color color) : image(image), color(color)
{
}

Actor::~Actor()
{
}

// 
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

void Actor::Tick(float deltaTime)
{
}

void Actor::Render()
{
	// Win32 API
	// Ŀ�� ��ġ �̵�.
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = (short)position.x;
	coord.Y = (short)position.y;

	SetConsoleCursorPosition(handle, coord);

	// ����
	SetConsoleTextAttribute(handle, (WORD)color);

	// �׸���
	std::cout << image;
	
}

void Actor::SetPosition(const Vector2& newPosition)
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	COORD coord;
	coord.X = (short)position.x;
	coord.Y = (short)position.y;

	SetConsoleCursorPosition(handle, coord);

	std::cout << ' ';

	position = newPosition;
}

Vector2 Actor::GetPosition() const
{
	return position;
}
