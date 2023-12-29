#pragma once
class DisjointSet
{
public:
	DisjointSet(int n) : _parent(n), _rank(n, 1)
	{
		for (int i = 0; i < n; i++)
		{
			_parent[i] = i; //자기 자신을 가리킴
		}
	}

	int Find(int u)
	{
		if (u == _parent[u]) return u;
		_parent[u] = Find(_parent[u]);
		return _parent[u];
	}

	void Union(int v, int u)
	{
		int u_parent = Find(u);
		int v_parent = Find(v);

		if (u_parent == v_parent) return;

		if (_rank[u_parent] > _rank[v_parent])
			swap(u_parent, v_parent);
		//rank[u] <= rank[v] 보장

		_parent[u_parent] = _parent[v_parent];

		//높이가 같으면 랭크가 1 증가 => 규칙있게 높이를 늘어남
		if (_rank[u_parent] == _rank[v_parent])
			_rank[v_parent]++;
	}

	void Print()
	{
		for (int i = 0; i < _parent.size(); i++)
			cout << _parent[i] << ' ';
		cout << '\n';
	}
private:

	vector<int> _parent;
	vector<int> _rank;
};