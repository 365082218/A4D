#pragma once
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
	static int Instance;
private:
	int instance;
};

