#pragma once
#include <iostream>
using namespace std;
class AObject
{
public:
	AObject(string n);
	AObject();
	~AObject();
	string name;
	static void Destroy(AObject * object);
	static void DestroyImmediate(AObject * object);
	int GetInstanceId();
private:
	int instance;
};

