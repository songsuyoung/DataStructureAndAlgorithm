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

	//시뮬레이션 - 오른손 법칙 

	Pos pos = _pos;
	Pos exitPos = board->GetExitPos();

	_path.clear();

	Bfs(pos, exitPos);
}


void Player::Update(uint64 deltaTick)
{
	//길찾기 알고리즘 수행
	//매초마다 움직이게 끔 수행

	//0.1초마다 움직일 수 있도록 구현
	//1초에 1 프레임
	if (_pathIdx >= _path.size()) return;

	_sumTick += deltaTick;

	if (_sumTick >= WORK_TICK) { //0.1초 경과
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
		// 현재 바라보는 방향을 기준으로 오른쪽으로 갈 수 있는지 확인
		/*
		현재 반시계 방향
		북0 - (오)동3
		서1 - (오)북0
		남2 - (오)서1
		동3 - (오)남2
		*/
		//오른쪽 방향 이동
		if (cnt == (_board->GetSize() * _board->GetSize()))
			break; //못나오는 경우

		int32 newDir = (D_COUNT + _dir - 1) % D_COUNT;

		Pos nextRight = Pos{ make_pair(pos.pos.first + rows[newDir], pos.pos.second + cols[newDir]) };
		Pos nextUp = Pos{ make_pair(pos.pos.first + rows[_dir], pos.pos.second + cols[_dir]) };

		if (CanGo(Pos{ nextRight }))
		{
			_dir = newDir;
			pos = nextRight;
			_path.push_back(nextRight);
			//오른쪽 비어있음 이동
		}
		else if (CanGo(Pos{ nextUp }))
		{
			//직선 비어있음 이동      
			pos = nextUp;
			_path.push_back(nextUp);
		}
		else
		{
			//왼쪽으로 회전
			_dir = (_dir + 1) % D_COUNT;
		}

		cnt++;
	}

	//path연산 후 제거하는 방식
	stack<Pos> s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		//s top과 같으면 더이상 가지 않고, s.top을 pop한다.
		if (!s.empty() && s.top() == _path[i + 1])
			s.pop();
		else // 한번만 갔을 때만 _path에 삽입한다.
			s.push(_path[i]);
	}
	//목적지라면? 삽입
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
	map<Pos, Pos> parent; //시작점은 자기 자신
	parent[start] = start;

	while (!q.empty())
	{
		Pos curPos = q.front();

		q.pop();
		if (isVisited[curPos.pos.first][curPos.pos.second]) continue;
		if (curPos == end)
		{
			//도착
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
	//거꾸로 올라감
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
