#pragma once
#include<vector>
using namespace std;
template<class T>
class Pool
{
public:
	Pool()
	{

	}
	~Pool()
	{

	}
	vector<T> items;
	void push(T handler)
	{
		items.push_back(handler);
	}
	T pop()
	{
		int i = items.size();
		if (i != 0)
			return items.pop_back();
		return NULL;
	}
};

