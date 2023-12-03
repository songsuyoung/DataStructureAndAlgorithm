#pragma once
class DrawBoard;
class Player
{
public:
	void Init(DrawBoard* board);
	void Update(uint64 deltaTick); //매 프레임마다 길찾기 알고리즘 수행

	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }
private:

	Pos _pos;
	int32 _dir = D_UP;
	DrawBoard* _board = nullptr;
};

