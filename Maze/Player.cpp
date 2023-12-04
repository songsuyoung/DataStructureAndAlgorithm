#include "pch.h"
#include "Player.h"
#include "DrawBoard.h"

void Player::Init(DrawBoard* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//시뮬레이션 - 오른손 법칙 

	Pos pos = _pos;
	Pos exitPos = board->GetExitPos();

	int rows[4] = {-1,0,1,0};
	int cols[4] = {0,-1,0,1};

	int cnt = 0;
	_path.clear();
	_path.push_back(_pos);

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

		Pos nextRight =Pos{ make_pair(pos.pos.first + rows[newDir], pos.pos.second + cols[newDir])};
		Pos nextUp = Pos{ make_pair(pos.pos.first + rows[_dir], pos.pos.second + cols[_dir]) };
		
		if (CanGo(Pos{ nextRight }))
		{
			//오른쪽 비어있음 이동
			_dir = newDir;
			pos = nextRight;
			_path.push_back(nextRight);
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
