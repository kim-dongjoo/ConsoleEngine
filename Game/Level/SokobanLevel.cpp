#include "SokobanLevel.h"
#include <iostream>
#include "Math/Vector2.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Box.h"
#include "Actor/Target.h"
#include "Utils/Utils.h"

SokobanLevel::SokobanLevel()
{
	ReadMapFile("Stage1.txt");
}

void SokobanLevel::Render()
{
	super::Render();

	if (isGameClear)
	{
		Utils::SetConsolePosition({ 30, 0 });
		Utils::SetConsoleTextColor(static_cast<WORD>(Color::White));

		std::cout << "==== Game Clear! ====";
	}

}

void SokobanLevel::ReadMapFile(const char* filename)
{
	// ���� �ּ� ��� �ϼ�
	char filepath[256] = {};
	sprintf_s(filepath, 256, "../Contents/%s", filename);

	FILE* file = nullptr;
	fopen_s(&file, filepath, "rt");

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
		case '1':
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
			targetScore++;
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

bool SokobanLevel::CheckGameClear()
{
	//  �ڽ��� Ÿ�� ��ġ�� ��� �Ű������� Ȯ��
	int currentScore = 0;

	// Ÿ�� ���� ���Ϳ� ����
	std::vector<Actor*> targetActors;
	std::vector<Actor*> boxActors;

	for (Actor* const actor : actors)
	{
		// Ÿ�� �������� Ȯ��
		if (actor->As<Target>())
		{
			targetActors.emplace_back(actor);
			continue;
		}

		// �ڽ� �������� Ȯ��
		if (actor->As<Box>())
		{
			boxActors.emplace_back(actor);
		}
	}

	// �ڽ��� Ÿ�� ��ġ ��
	for (Actor* const targetActor : targetActors)
	{
		for (Actor* const boxActor : boxActors)
		{
			if (targetActor->GetPosition() == boxActor->GetPosition())
			{
				// ���� ����
				++currentScore;
			}
		}
	}


	return currentScore == targetScore;



	return false;
}

bool SokobanLevel::CanPlayerMove(const Vector2& playerPosition, const Vector2& newPosition)
{
	// ���� Ŭ���� ���� Ȯ�� �� ���� ó��
	if (isGameClear)
	{
		return false;
	}

	// �ڽ� ó��
	std::vector<Box*> boxActors;
	for (Actor* const actor : actors)
	{
		Box* box = actor->As<Box>();
		if (box)
		{
			boxActors.emplace_back(box);
		}
	}

	// �̵��Ϸ��� ��ġ�� �ڽ��� �ִ��� Ȯ��
	Box* searchedBox = nullptr;
	for (Box* const boxActor : boxActors)
	{
		// �÷��̾ �̵��Ϸ��� ��ġ�� �ڽ��� ��ġ�� ������ ��
		if (boxActor->GetPosition() == newPosition)
		{
			// ���� ��ġ�� �ִ� �ڽ� ���� �� ���� ����
			searchedBox = boxActor;
			break;
		}
	}

	// �̵��Ϸ��� ��ġ�� �ڽ��� �ִ� ��� ó��
	if (searchedBox)
	{
		// 1. �ڽ��� �̵���Ű���� ��ġ�� �ٸ� �ڽ��� �ִ��� Ȯ��.
		Vector2 direction = newPosition - playerPosition;
		Vector2 nextPosition = searchedBox->GetPosition() + direction;

		for (Box* const otherBox : boxActors)
		{
			// ���� �ڽ��� �ǳʶٱ�
			if (otherBox == searchedBox)
				continue;

			if (otherBox->GetPosition() == nextPosition)
			{
				// �÷��̾� �̵� ����
				return false;
			}
		}

		for (Actor* const actor : actors)
		{
			if (actor->GetPosition() == nextPosition)
			{
				// 2. �ڽ��� �̵���Ű���� ��ġ�� ���� �ִ��� Ȯ��

				if (actor->As<Wall>())
				{
					// �÷��̾� �̵� ����
					return false;
				}

				// 3. �̵� ������ ���(�׶���/Ÿ��) �̵�ó��
				if (actor->As<Ground>() || actor->As<Target>())
				{
					// �ڽ� �̵� ó��
					searchedBox->SetPosition(nextPosition);

					// ���� Ŭ���� ���� Ȯ��
					isGameClear = CheckGameClear();

					// �÷��̾� �̵� ����
						return true;
				}
			}
		}
	}

	// �÷��̾ �̵��Ϸ��� ��ġ�� �ڽ��� ���� ���
	for (Actor* const actor : actors)
	{
		if (actor->GetPosition() == newPosition)
		{
			// ���̸� �̵� �Ұ�
			if (actor->As<Wall>())
			{
				return false;
			}

			// �׶��� or Ÿ��
			return true;
		}
	}

	return false;
}
