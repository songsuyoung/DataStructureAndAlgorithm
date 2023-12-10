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

	Bfs(pos, exitPos);
}


void Player::Update(uint64 deltaTick)
{
	//��ã�� �˰��� ����
	//���ʸ��� �����̰� �� ����

	//0.1�ʸ��� ������ �� �ֵ��� ����
	//1�ʿ� 1 ������
	if (_pathIdx >= _path.size()) return;

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
		// ���� �ٶ󺸴� ������ �������� ���������� �� �� �ִ��� Ȯ��
		/*
		���� �ݽð� ����
		��0 - (��)��3
		��1 - (��)��0
		��2 - (��)��1
		��3 - (��)��2
		*/
		//������ ���� �̵�
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
