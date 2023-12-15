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
	void Update(uint64 deltaTick); //�� �����Ӹ��� ��ã�� �˰���� ����
	void SetPos(Pos pos) { _pos = pos; }
	Pos GetPos() { return _pos; }
	bool CanGo(Pos pos);

private:
	void FindRightHands(const Pos& start, const Pos& end);
	void Bfs(Pos& start,Pos& end);
	void AStar(Pos& start, Pos& end);
private:

	Pos _pos;
	int32 _dir = D_UP;
	DrawBoard* _board = nullptr;
	
	uint64 _sumTick = 0;
	uint32 _pathIdx = 0;
	vector<Pos> _path;
};

