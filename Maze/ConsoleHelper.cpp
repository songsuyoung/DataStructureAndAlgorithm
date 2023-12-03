#include "pch.h"
#include "ConsoleHelper.h"
//맵을 그려주는 역할 

void ConsoleHelper::SetCursorPosition(int32 x, int32 y)
{
	//클릭한 위치를 설정
	//윈도우 함수
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	//coordinate 좌표에 대한 구조체를 가져와서
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos); //커서 위치를 변경
}

void ConsoleHelper::SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<int16>(color));
}

void ConsoleHelper::ShowCursolConsole(bool flag)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO	cursorInfo;
	::GetConsoleCursorInfo(output, &cursorInfo);
	cursorInfo.bVisible = flag;
	::SetConsoleCursorInfo(output, &cursorInfo);
}
