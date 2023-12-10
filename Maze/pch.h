#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>
#include "type.h"
using namespace std;

//좌표 관리용
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
	bool operator<(const Pos& other) const
	{
		if (this->pos.first == other.pos.first) return pos.second < other.pos.second;
		return pos.first < other.pos.first;
	}
};

enum Dir
{
	//반시계 방향으로 구현
	D_UP=0,
	D_LEFT,
	D_DOWN,
	D_RIGHT,

	D_COUNT=4,
};