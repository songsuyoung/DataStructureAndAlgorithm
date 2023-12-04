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

//Binary Tree 미로 생성 알고리즘
/* Mazes For Programmers */
void DrawBoard::GenerateMap()
{
	for (int r = 0; r < _size; r++)
	{
		for (int c = 0; c < _size; c++)
		{
			if (r == 0 || c == 0 || r==(_size-1)|| c==(_size-1)|| r % 2 == 0 || c % 2 == 0)
			{
				//외곽
				_tile[r][c] = TileType::WALL;
			}
			else
			{
				//내부
				_tile[r][c] = TileType::EMPTY;
			}
		}
	}

	//벽 뚫기 작업 
	
	for (int r = 0; r < _size; r++)
	{
		for (int c = 0; c < _size; c++)
		{
			//벽일때는 안뚫음!
			if (r % 2 == 0 || c % 2 == 0) continue;				
			//2분의 1 확률로 오른쪽을 뚫거나 아래를 뚫을 예정
			
			const int32 randVal = ::rand() % 2;
			if (randVal == 0) //오른쪽
			{
				if (c + 1 == (_size - 1)) continue;
				_tile[r][c + 1] = TileType::EMPTY;
			}
			else //아래
			{
				if (r + 1 == (_size - 1)) continue;
				_tile[r + 1][c] = TileType::EMPTY;
			}
		}
	}
	

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
			ConsoleColor color = GetTileColor(Pos{make_pair(r,c)}); //초기화 리스트 사용
			ConsoleHelper::SetCursorColor(color);
			cout << TILE;
		}
		cout << endl;
	}
}
