#pragma once
class DrawBoard;
class Player
{
public:
	void Init(DrawBoard* board);
	void Update(uint64 deltaTick); //�� �����Ӹ��� ��ã�� �˰��� ����

	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }
private:

	Pos _pos;
	int32 _dir = D_UP;
	DrawBoard* _board = nullptr;
};

