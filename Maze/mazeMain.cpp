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
#pragma region 프레임 관리 : 1초동안 60프레임 통과시켜야함
		//현재 시간
		const uint64 currentTick = ::GetTickCount64();
		const uint64 deltaTick = currentTick - lastTick; //경과 시간
		lastTick = deltaTick; 
#pragma endregion
		//입력 - 키보드,마우스

		//로직 - 플레이어 이동, 몬스터AI

		//렌더링 - 게임을 컴퓨터 내 구현

		//맵을 그려줌 
		board.Render();
	}
}