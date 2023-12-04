#pragma once
class DrawBoard;
class Player
{
	enum
	{
		WORK_TICK = 100,
	};
public:
	void Init(DrawBoard* board);
	void Update(uint64 deltaTick); //�� �����Ӹ��� ��ã�� �˰��� ����
	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }
	bool CanGo(Pos pos);
private:

	Pos _pos;
	int32 _dir = D_UP;
	DrawBoard* _board = nullptr;
	
	uint64 _sumTick = 0;
	uint32 _pathIdx = 0;
	vector<Pos> _path;
};

