#include "pch.h"
#include "Player.h"
#include "DrawBoard.h"

void Player::Init(DrawBoard* board)
{
	_pos = board->GetEnterPos();
	_board = board;
}

void Player::Update(uint64 deltaTick)
{
	//��ã�� �˰��� ����
	//���ʸ��� �����̰� �� ����
}
