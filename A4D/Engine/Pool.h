#pragma once
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
	void recover(T handler)
	{
		items.push_back(handler);
	}
	T alloc()
	{
		int i = items.size();
		if (i != 0)
			return items.pop_back();
		return NULL;
	}
};

