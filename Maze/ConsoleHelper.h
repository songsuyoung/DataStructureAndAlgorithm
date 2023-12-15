#pragma once
#include <Windows.h>
#include "type.h"
//���� ����
enum class ConsoleColor
{
	BLACK=0,
	RED= FOREGROUND_RED,
	BLUE= FOREGROUND_BLUE,
	GREEN= FOREGROUND_GREEN,
	YELLOW = RED | GREEN,
	WHITE = RED|GREEN|BLUE,
};
//�ϳ��� �����ϱ� ������ ���� �Լ��� ����, �̷� �ܼ��� �����ִ� Ŭ����
class ConsoleHelper
{
public:
	static void SetCursorPosition(int32 x, int32 y); //32����Ʈ�� ����ϴ� ���� : ���� �ػ󵵿� ���߱� ������
	static void SetCursorColor(ConsoleColor colr);
	static void ShowCursolConsole(bool flag); //Ŀ���� �������� �Ⱥ������� ����
};

