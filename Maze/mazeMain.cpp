#include <iostream>
#include "pch.h"
#include "ConsoleHelper.h"
#include "DrawBoard.h"
#include "Player.h"
int main()
{

	srand(static_cast<unsigned int>(time(nullptr)));
	uint64 lastTick = 0;
	DrawBoard board;
	Player player;
	board.Init(25,&player);
	player.Init(&board);
	while (true)
	{
#pragma region ������ ���� : 1�ʵ��� 60������ ������Ѿ���
		//���� �ð�
		const uint64 currentTick = ::GetTickCount64();
		const uint64 deltaTick = currentTick - lastTick; //��� �ð�
		lastTick = deltaTick; 
#pragma endregion
		//�Է� - Ű����,���콺

		//���� - �÷��̾� �̵�, ����AI

		//������ - ������ ��ǻ�� �� ����

		//���� �׷��� 
		board.Render();
	}
}