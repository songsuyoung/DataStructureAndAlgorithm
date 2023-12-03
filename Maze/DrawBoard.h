#pragma once
#include "ConsoleHelper.h"
enum
{
	BOARD_MAX_SIZE = 100,
};

enum class TileType
{
	NONE = 0,//아직 없음
	EMPTY, //건널 수 있음
	WALL, //벽
	CURRPOS, //입장
	EXIT, //탈출
};
class  Player; //전방 선언을 이용해서 헤더 파일 선언하지 않도록 해줌
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
	const char* TILE = "■"; //const char 는 문자열을 의미
	TileType _tile[BOARD_MAX_SIZE][BOARD_MAX_SIZE];
	int32 _size = 0;
	Player* _player = nullptr;
};

