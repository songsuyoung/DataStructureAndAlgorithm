#include "pch.h"
#include "ConsoleHelper.h"
//���� �׷��ִ� ���� 

void ConsoleHelper::SetCursorPosition(int32 x, int32 y)
{
	//Ŭ���� ��ġ�� ����
	//������ �Լ�
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	//coordinate ��ǥ�� ���� ����ü�� �����ͼ�
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos); //Ŀ�� ��ġ�� ����
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
