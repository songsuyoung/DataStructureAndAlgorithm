#include "pch.h"
#include "DrawBoard.h"
#include "ConsoleHelper.h"
#include "Player.h"

void DrawBoard::Init(int32 size,Player *player)
{
	_player = player;
	
	_size = size;
	GenerateMap();
}

//Binary Tree �̷� ���� �˰����
/* Mazes For Programmers */
void DrawBoard::GenerateMap()
{
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_tile[y][x] = TileType::WALL;
			else
				_tile[y][x] = TileType::EMPTY;
		}
	}

	// 랜덤으로 우측 혹은 아래로 길을 뚫는 작업
	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;
			if (y == _size - 2 && x == _size - 2)
				continue;

			if (y == _size - 2)
			{
				_tile[y][x + 1] = TileType::EMPTY;
				continue;
			}

			if (x == _size - 2)
			{
				_tile[y + 1][x] = TileType::EMPTY;
				continue;
			}

			const int32 randValue = ::rand() % 2;
			if (randValue == 0)
			{
				_tile[y][x + 1] = TileType::EMPTY;
			}
			else
			{
				_tile[y + 1][x] = TileType::EMPTY;
			}
		}
	}
	//for (int r = 0; r < _size; r++)
	//{
	//	for (int c = 0; c < _size; c++)
	//	{
	//		if (r == 0 || c == 0 || r==(_size-1)|| c==(_size-1)|| r % 2 == 0 || c % 2 == 0)
	//		{
	//			//�ܰ�
	//			_tile[r][c] = TileType::WALL;
	//		}
	//		else
	//		{
	//			//����
	//			_tile[r][c] = TileType::EMPTY;
	//		}
	//	}
	//}

	////�� �ձ� �۾� 
	//
	//for (int r = 0; r < _size; r++)
	//{
	//	for (int c = 0; c < _size; c++)
	//	{
	//		//���϶��� �ȶ���!
	//		if (r % 2 == 0 || c % 2 == 0) continue;				
	//		//2���� 1 Ȯ���� �������� �հų� �Ʒ��� ���� ����
	//		
	//		const int32 randVal = ::rand() % 2;
	//		if (randVal == 0) //������
	//		{
	//			if (c + 1 == (_size - 1)) continue;
	//			_tile[r][c + 1] = TileType::EMPTY;
	//		}
	//		else //�Ʒ�
	//		{
	//			if (r + 1 == (_size - 1)) continue;
	//			_tile[r + 1][c] = TileType::EMPTY;
	//		}
	//	}
	//}
	//

}

TileType DrawBoard::GetTileType(Pos pos)
{
	if (GetExitPos() == pos)
		return TileType::EXIT;
	if (_player!=nullptr&& _player->GetPos() == pos)
		return TileType::CURRPOS;

	if (pos.pos.first < 0 || pos.pos.second < 0 || pos.pos.first >= _size || pos.pos.second >= _size)
		return TileType::NONE;

	return _tile[pos.pos.first][pos.pos.second];
}

ConsoleColor DrawBoard::GetTileColor(Pos pos)
{
	TileType type=GetTileType(pos);

	switch (type)
	{
	case TileType::EMPTY:
		return ConsoleColor::YELLOW;
	case TileType::WALL:
		return ConsoleColor::WHITE;
	case TileType::CURRPOS:
		return ConsoleColor::GREEN;
	case TileType::EXIT:
		return ConsoleColor::RED;
	}

	return ConsoleColor::BLACK; //default
}

void DrawBoard::Render()
{
	ConsoleHelper::SetCursorPosition(0, 0);
	ConsoleHelper::ShowCursolConsole(false);

	for (int32 r = 0; r < _size; r++)
	{
		for (int32 c = 0; c < _size; c++)
		{
			ConsoleColor color = GetTileColor(Pos{make_pair(r,c)}); //�ʱ�ȭ ����Ʈ ���
			ConsoleHelper::SetCursorColor(color);
			cout << TILE;
		}
		cout << endl;
	}
}
