#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>
#include "type.h"
using namespace std;

//��ǥ ������
struct Pos
{
	pair<int32, int32> pos;
	bool operator==(Pos& other)
	{
		return pos == other.pos;
	}

	bool operator!=(Pos& other)
	{
		return !(*this == other);
	}

	Pos operator+(Pos& other)
	{
		Pos tmp;
		tmp.pos.first += other.pos.first;
		tmp.pos.second += other.pos.second;

		return tmp;
	}

	Pos& operator+=(Pos& other)
	{
		pos.first += other.pos.first;
		pos.second += other.pos.second;

		return *this;
	}
};

enum Dir
{
	//�ݽð� �������� ����
	D_UP=0,
	D_LEFT,
	D_DOWN,
	D_RIGHT,

	D_COUNT=4,
};