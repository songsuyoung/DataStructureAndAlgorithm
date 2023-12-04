#include "pch.h"
#include "Player.h"
#include "DrawBoard.h"

void Player::Init(DrawBoard* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//�ùķ��̼� - ������ ��Ģ 

	Pos pos = _pos;
	Pos exitPos = board->GetExitPos();

	int rows[4] = {-1,0,1,0};
	int cols[4] = {0,-1,0,1};

	int cnt = 0;
	_path.clear();
	_path.push_back(_pos);

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

		Pos nextRight =Pos{ make_pair(pos.pos.first + rows[newDir], pos.pos.second + cols[newDir])};
		Pos nextUp = Pos{ make_pair(pos.pos.first + rows[_dir], pos.pos.second + cols[_dir]) };
		
		if (CanGo(Pos{ nextRight }))
		{
			//������ ������� �̵�
			_dir = newDir;
			pos = nextRight;
			_path.push_back(nextRight);
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
