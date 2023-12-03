#pragma once
#include "ConsoleHelper.h"
enum
{
	BOARD_MAX_SIZE = 100,
};

enum class TileType
{
	NONE = 0,//���� ����
	EMPTY, //�ǳ� �� ����
	WALL, //��
	CURRPOS, //����
	EXIT, //Ż��
};
class  Player; //���� ������ �̿��ؼ� ��� ���� �������� �ʵ��� ����
class DrawBoard
{
public:
	DrawBoard(){}
	~DrawBoard() {}

	void Init(int32 size,Player* player);
	void GenerateMap();
	TileType GetTileType(Pos pos);
	ConsoleColor GetTileColor(Pos pos);
	void Render();

	Pos GetEnterPos() { return Pos{ make_pair(1,1) }; }
	Pos GetExitPos() { return Pos{ make_pair(_size-2,_size-2) }; }

private:
	const char* TILE = "��"; //const char �� ���ڿ��� �ǹ�
	TileType _tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE];
	int32 _size = 0;
	Player* _player = nullptr;
};

