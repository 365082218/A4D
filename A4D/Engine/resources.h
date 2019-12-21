#pragma once
#include "Time.h"
class Resource :
	public EventDispatcher
{
public:
	static int _uniqueIDCounter;
	static map<int, Resource*> _idResourcesMap;
	Resource();
	~Resource();
	int id;
	bool loaded;
	bool destroyed;
	int referenceCount = 0;
	bool released = true;
	bool lock = false;
	int memorySize = 0;
	int lastUseFrameCount = -1;
	void _addReference()
	{
		this->referenceCount++;
	}
	void _removeReference()
	{
		this->referenceCount--;
	}
	void _clearReference()
	{
		this->referenceCount = 0;
	}

	virtual void recreateResource()
	{
		completeCreate();
	}

	virtual void completeCreate()
	{

	}

	virtual void activeResource(bool force = false){
		lastUseFrameCount = Time::frame;
		if (!destroyed && loaded && (released || force))
			recreateResource();
	}
};
