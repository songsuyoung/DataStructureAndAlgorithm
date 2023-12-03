#pragma once
#include <Windows.h>
#include "type.h"
//색상 지정
enum class ConsoleColor
{
	BLACK=0,
	RED= FOREGROUND_RED,
	BLUE= FOREGROUND_BLUE,
	GREEN= FOREGROUND_GREEN,
	YELLOW = RED | GREEN,
	WHITE = RED|GREEN|BLUE,
};
//하나만 존재하기 때문에 정적 함수로 선언, 미로 콘솔을 도와주는 클래스
class ConsoleHelper
{
public:
	static void SetCursorPosition(int32 x, int32 y); //32바이트를 사용하는 이유 : 현재 해상도에 맞추기 때문에
	static void SetCursorColor(ConsoleColor colr);
	static void ShowCursolConsole(bool flag); //커서를 보여줄지 안보여줄지 결정
};

