#include "SokobanLevel.h"
#include <iostream>
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"

SokobanLevel::SokobanLevel()
{
	ReadMapFile("Map.txt");
}

void SokobanLevel::ReadMapFile(const char* filename)
{
	// ���� �ּ� ��� �ϼ�
	char filepath[256] = {};
	sprintf_s(filepath, 256, "../Contents/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rb");

	// ���� ó��
	if (file == nullptr)
	{
		std::cout << "�� ���� �б� ���� (" << filename << ")" << std::endl;
		__debugbreak();
		return;
	}

	// �Ľ�
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	// Ȯ���� ���� ũ�⸦ Ȱ���� ���� �Ҵ�.
	char* buffer = new char[fileSize + 1];
	// memset(buffer, 0, fileSize + 1);
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);
	buffer[fileSize] = '\0';

	if (fileSize != readSize)
	{
		std::cout << "fileSize is not matched with readSize. \n";
	}

	// �迭 ��ȸ�� ���� �ε��� ����
	int index = 0;

	// ���ڿ� ���̰�
	int size = (int)readSize;

	// x, y ��ǥ
	Vector2 position;

	// ���� �迭 ��ȸ
	while (index < size)
	{
		// �� ���� Ȯ��
		char mapCharacter = buffer[index++];

		// ���� ���� ó��
		if (mapCharacter == '\n')
		{
			++position.y;
			position.x = 0;

			// �׽�Ʈ �ڵ�
			std::cout << std::endl;
			continue;
		}

		switch (mapCharacter)
		{
		case '#':
			SpawnActor(new Wall(position));
			// std::cout << "#";
			break;
		case '.':
			SpawnActor(new Ground(position));
			// std::cout << ".";
			break;
		case 'p':
			// ���� ���� ����
			SpawnActor(new Ground(position));
			// std::cout << "p";
			SpawnActor(new Player(position));
			break;
		case 'b':
			// ���� ���� ����
			SpawnActor(new Ground(position));
			SpawnActor(new Box(position));
			// std::cout << "b";
			break;
		case 't':
			SpawnActor(new Target(position));
			// std::cout << "t";
			break;
		}

		// x ��ǥ ���� ó��
		++position.x;
	}

	// ���� ����
	delete[] buffer;

	// ���� �ݱ�
	fclose(file);

}
