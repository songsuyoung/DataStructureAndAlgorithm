#include "pch.h"
#include "Player.h"
#include "DrawBoard.h"
#include <stack>
#include <queue>
#include <map>
void Player::Init(DrawBoard* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//�ùķ��̼� - ������ ��Ģ 

	Pos pos = _pos;
	Pos exitPos = board->GetExitPos();

	_path.clear();

	AStar(pos, exitPos);
}


void Player::Update(uint64 deltaTick)
{
	if (_pathIdx >= _path.size())
	{
		_board->GenerateMap_PrimAlgorithm();
		Init(_board);
		return;
	}

	_sumTick += deltaTick;

	if (_sumTick >= WORK_TICK) { //0.1�� ���
		_sumTick = 0;
		_pos = _path[_pathIdx];
		_pathIdx++;
	}

}

bool Player::CanGo(Pos pos)
{
	return _board->GetTileType(pos) != TileType::WALL;
}

void Player::FindRightHands(const Pos &start, const Pos &end)
{

	Pos pos = start;
	Pos exitPos = end;

	int rows[4] = { -1,0,1,0 };
	int cols[4] = { 0,-1,0,1 };

	int cnt = 0;
	while (pos != exitPos)
	{
		if (cnt == (_board->GetSize() * _board->GetSize()))
			break; //�������� ���

		int32 newDir = (D_COUNT + _dir - 1) % D_COUNT;

		Pos nextRight = Pos{ make_pair(pos.pos.first + rows[newDir], pos.pos.second + cols[newDir]) };
		Pos nextUp = Pos{ make_pair(pos.pos.first + rows[_dir], pos.pos.second + cols[_dir]) };

		if (CanGo(Pos{ nextRight }))
		{
			_dir = newDir;
			pos = nextRight;
			_path.push_back(nextRight);
			//������ ������� �̵�
		}
		else if (CanGo(Pos{ nextUp }))
		{
			//���� ������� �̵�      
			pos = nextUp;
			_path.push_back(nextUp);
		}
		else
		{
			//�������� ȸ��
			_dir = (_dir + 1) % D_COUNT;
		}

		cnt++;
	}

	//path���� �� �����ϴ� ���
	stack<Pos> s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		//s top�� ������ ���̻� ���� �ʰ�, s.top�� pop�Ѵ�.
		if (!s.empty() && s.top() == _path[i + 1])
			s.pop();
		else // �ѹ��� ���� ���� _path�� �����Ѵ�.
			s.push(_path[i]);
	}
	//���������? ����
	if (_path.empty() == false)
		s.push(_path.back());

	vector<Pos> path;
	while (!s.empty())
	{
		path.push_back(s.top());
		s.pop();
	}

	std::reverse(path.begin(), path.end());
	_path = path;
}

void Player::Bfs(Pos& start, Pos& end)
{

	int rows[4] = { -1,0,1,0 };
	int cols[4] = { 0,-1,0,1 };

	queue<Pos> q;
	q.push(start);

	const int32 SIZE = _board->GetSize();
	vector<vector<bool>> isVisited(SIZE, vector<bool>(SIZE, false));
	map<Pos, Pos> parent; //�������� �ڱ� �ڽ�
	parent[start] = start;

	while (!q.empty())
	{
		Pos curPos = q.front();

		q.pop();
		if (isVisited[curPos.pos.first][curPos.pos.second]) continue;
		if (curPos == end)
		{
			//����
			break;
		}
		isVisited[curPos.pos.first][curPos.pos.second] = true;

		for (int i = 0; i < 4; i++)
		{
			int nextR = curPos.pos.first + rows[i];
			int nextC = curPos.pos.second + cols[i];

			if (nextR < 0 || nextR >= SIZE || nextC < 0 || nextC >= SIZE || CanGo(Pos{ make_pair(nextR,nextC)})==false) continue;

			q.push(Pos{ make_pair(nextR, nextC) });

			if (isVisited[nextR][nextC]==false) {
				parent[Pos{ make_pair(nextR,nextC) }] = curPos;
			}
		}
	}
	//�Ųٷ� �ö�
	Pos pos = end;
	while (true)
	{
		_path.push_back(pos);
		if (pos == parent[pos])
			break;
		pos = parent[pos];
	}

	reverse(_path.begin(), _path.end());
}
struct PQNode
{
	bool operator<(const PQNode& other) const
	{
		return f < other.f;
	}
	bool operator>(const PQNode& other) const
	{
		return f > other.f;
	}
	int32 f;
	int32 g;
	Pos p;
};

int32 GetHeuristic(int cost,const pair<int,int> &dest,const pair<int,int> &start)
{
	//row 차이와 col 차이에 대해 비용 단위를 곱함 
	//피타고라스의 정의를 이용해서 distance를 구할 수 있음.
	return cost * (abs(dest.first - start.first) + abs(dest.second - start.second));
}
void Player::AStar(Pos& start, Pos& end)
{

	//점수 매기기 -> 평가 시스템
	//가중치의 합(dijkstra)
	//F = G + H(Heuristic)
	//F = 최종 점수 (작을 수록 좋음, 경로에 따라 달라짐)
	//G = 시작점에서 해당 좌표까지의 비용 (작을 수록 좋음 또한, 경로에 따라 달라짐)
	//H = 목적지에서 얼마나 가까운지 (작을 수록 좋음, 고정)

	//UP,LEFT,DOWN,RIGHT,UP-LEFT,DOWN-LEFT,DOWN-RIGHT,UP-RIGHT

	int rows[8] = { -1,0,1,0,-1,1,1,-1 };
	int cols[8] = { 0,-1,0,1,-1,-1,1,1 };

	//1:1:루트2 공식에 의해서 cost비용을 14로 형평성 있게 일치 시켜줌.
	int32 cost[] = { 10, 10, 10, 10, 14, 14, 14, 14};

	const int32 SIZE = _board->GetSize();

	map<Pos, Pos> parent; //부모 추적 용도
	
	//OpenList (예약된(즉 방문할) 노드)
	priority_queue<PQNode> q;
	
	//[r,c]에 대한 지금까지 가장 좋은 비용
	vector<vector<int32>> best(SIZE, vector<int32>(SIZE,INT32_MAX));
	//이중 방문을 막아줌, ClosedList (이미 방문된 노드)
	vector<vector<bool>> isVisited(SIZE, vector<bool>(SIZE, false));

	// 1) 예약(발견) 시스템 구현
	// 2) 뒤 늦게 더 좋은 경로가 발견될 수 있음 -> 예외 처리 필수 : priority_queue
	{
		int g = 0;//시작점
		int h = GetHeuristic(cost[0], end.pos, start.pos);
		q.push( PQNode{ g+h,g,start });
		best[start.pos.first][start.pos.second] = g + h;
		parent[start] = start;
	}
	
	while (!q.empty())
	{
		PQNode cur = q.top();
		q.pop();

		if (isVisited[cur.p.pos.first][cur.p.pos.second]) continue;
		//방문 했으니, ClosedNode를 이용해 나 이미 방문 했어.
		isVisited[cur.p.pos.first][cur.p.pos.second] = true;
	
		if (cur.p == end) break; //도착하였음.

		for (int32 dir = 0; dir < D_COUNT; dir++)
		{
			int nextR = cur.p.pos.first + rows[dir];
			int nextC = cur.p.pos.second + cols[dir];

			Pos nextPos = Pos{ make_pair(nextR,nextC) };
			int32 g = cur.g+cost[dir];
			int32 h = GetHeuristic(cost[dir], make_pair(nextR,nextC), cur.p.pos);

			if (CanGo(nextPos) == false) continue;
			if (isVisited[nextR][nextC]==false&&best[nextR][nextC] > (g + h))
			{
				best[nextR][nextC] = g + h; //갱신
				q.push({ g + h,g,nextPos});
				parent[nextPos] = cur.p;
			}
		}
	}
	_path.clear();
	Pos pos = end;
	while (true)
	{
		_path.push_back(pos);
		if (pos == parent[pos])
			break;
		pos = parent[pos];
	}
	_pathIdx = 0;
	reverse(_path.begin(), _path.end());
}
