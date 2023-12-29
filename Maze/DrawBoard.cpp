#include "pch.h"
#include "DrawBoard.h"
#include "ConsoleHelper.h"
#include "Player.h"
#include "DisjointSet.h"
#include <queue>
#include <map>

void DrawBoard::Init(int32 size,Player *player)
{
	_player = player;
	
	_size = size;
	GenerateMap_PrimAlgorithm();
}

void DrawBoard::GenerateMap_PrimAlgorithm()
{
	struct CostEdge
	{ //2차원 좌표
		Pos u;
		int cost;

		bool operator<(const CostEdge& other) const
		{
			return cost < other.cost;
		}
	};

	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_tile[y][x] = TileType::WALL;
			else
				_tile[y][x] = TileType::EMPTY;
		}
	}


	map<Pos, vector<CostEdge>> edges;

	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0) continue; //벽일 때임

			//우측 연결하는 간선 후보
			if (x < _size - 2) //벽이 아닐때, [u] [wall] [v] 로 구성해서 u-v간의 길이를 표현
			{
				const int32 randVal = static_cast<int32>(rand() % 100 + 1);
				//맨 끝에 도달하지 않았다.
				Pos u = Pos{ make_pair(y,x) };
				Pos v = Pos{ make_pair(y,x + 2) };

				edges[u].push_back(CostEdge{ v,randVal });
			}
			if (y < _size - 2)
			{
				//맨 끝에 도달하지 않았다.
				const int32 randVal = static_cast<int32>(rand() % 100 + 1);
				//맨 끝에 도달하지 않았다.
				Pos u = Pos{ make_pair(y,x) };
				Pos v = Pos{ make_pair(y+2,x) };

				edges[u].push_back(CostEdge{ v,randVal });
			}
		}
	}

	priority_queue<CostEdge> pq;
	map<Pos, bool> isVisited;
	map<Pos, Pos> parent;
	map<Pos, int32> best; 


	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			best[Pos{ make_pair(y,x) }] = INT32_MAX;
			isVisited[Pos{ make_pair(y,x) }] = false;
		}
	}

	Pos startPos = Pos{ make_pair(1,1) };
	pq.push(CostEdge{ startPos,0 });
	best[startPos] = 0;
	parent[startPos] = startPos;

	while (!pq.empty())
	{
		CostEdge cur = pq.top();
		pq.pop();

		if (isVisited[cur.u]) continue;
		isVisited[cur.u] = true;

		int row = (parent[cur.u].pos.first + cur.u.pos.first) / 2;
		int col = (parent[cur.u].pos.second + cur.u.pos.second) / 2;

		_tile[row][col] = TileType::EMPTY;

		for (int i = 0; i < edges[cur.u].size(); i++)
		{
			if (isVisited[edges[cur.u][i].u]) continue;
			CostEdge next = edges[cur.u][i];
			int costs = edges[cur.u][i].cost;
			if (best[next.u] > costs)
			{
				best[next.u] = costs;
				parent[edges[cur.u][i].u] = cur.u;
				pq.push(edges[cur.u][i]);
			}
		}
	}

}


//Binary Tree 생성 알고리즘 => Kruskal 도입
/* Mazes For Programmers */
void DrawBoard::GenerateMap_KruskalAlgorithm()
{
	struct CostEdge
	{ //2차원 좌표
		Pos u;
		Pos v;
		int cost;

		bool operator<(const CostEdge& other)
		{
			return cost < other.cost;
		}
	};

	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				_tile[y][x] = TileType::WALL;
			else
				_tile[y][x] = TileType::EMPTY;
		}
	}

	//랜덤으로 수를 뚫어줌
	vector<CostEdge> edges;

	for (int32 y = 0; y < _size; y++)
	{
		for (int32 x = 0; x < _size; x++)
		{
			if (x % 2 == 0 || y % 2 == 0) continue; //벽일 때임

			//우측 연결하는 간선 후보
			if (x < _size - 2) //벽이 아닐때, [u] [wall] [v] 로 구성해서 u-v간의 길이를 표현
			{
				//맨 끝에 도달하지 않았다.
				const int32 randVal = static_cast<int32>(rand() % 100+1);
				edges.push_back(CostEdge{ Pos{make_pair(y,x)},Pos{make_pair(y,x+2)},randVal });
			}

			if (y < _size - 2)
			{
				//맨 끝에 도달하지 않았다.
				const int32 randVal = static_cast<int32>(rand() % 100 + 1);
				edges.push_back(CostEdge{ Pos{make_pair(y,x)},Pos{make_pair(y+2,x)},randVal });
			}
		}
	}

	std::sort(edges.begin(), edges.end()); //작은 순서로 정렬

	DisjointSet ds(_size* _size);

	for (int i = 0; i < edges.size(); i++)
	{
		//1차원 배열로 관리하기 위함.
		int u = edges[i].u.pos.first * _size + edges[i].u.pos.second;
		int v = edges[i].v.pos.first * _size + edges[i].v.pos.second;
		if (ds.Find(u) != ds.Find(v))
		{
			ds.Union(u, v);

			//[u] [wall] [v]  <- 설정되어있음.
			// 중간 값을 u+v 좌표 /2 를 수행
			int row = (edges[i].u.pos.first + edges[i].v.pos.first) / 2;
			int col = (edges[i].u.pos.second + edges[i].v.pos.second) / 2;
			_tile[row][col] = TileType::EMPTY;
		}
	}
}

TileType DrawBoard::GetTileType(Pos pos)
{
	if (GetExitPos() == pos)
		return TileType::EXIT;
	if (_player!=nullptr&& _player->GetPos() == pos)
		return TileType::CURRPOS;

	if (pos.pos.first < 0 || pos.pos.second < 0 || pos.pos.first >= _size || pos.pos.second >= _size)
		return TileType::NONE;

	return _tile[pos.pos.first][pos.pos.second];
}

ConsoleColor DrawBoard::GetTileColor(Pos pos)
{
	TileType type=GetTileType(pos);

	switch (type)
	{
	case TileType::EMPTY:
		return ConsoleColor::YELLOW;
	case TileType::WALL:
		return ConsoleColor::WHITE;
	case TileType::CURRPOS:
		return ConsoleColor::GREEN;
	case TileType::EXIT:
		return ConsoleColor::RED;
	}

	return ConsoleColor::BLACK; //default
}

void DrawBoard::Render()
{
	ConsoleHelper::SetCursorPosition(0, 0);
	ConsoleHelper::ShowCursolConsole(false);

	for (int32 r = 0; r < _size; r++)
	{
		for (int32 c = 0; c < _size; c++)
		{
			ConsoleColor color = GetTileColor(Pos{make_pair(r,c)}); //�ʱ�ȭ ����Ʈ ���
			ConsoleHelper::SetCursorColor(color);
			cout << TILE;
		}
		cout << endl;
	}
}
