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
	//길찾기 알고리즘 수행
	//매초마다 움직이게 끔 수행
}
