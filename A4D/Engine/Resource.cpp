#include "stdafx.h"
#include "Resources.h"
#include "Pool.h"
#include "Time.h"
int Resource::_uniqueIDCounter = 0;
map<int, Resource*> Resource::_idResourcesMap;
Resource::Resource()
{
	id = ++ Resource::_uniqueIDCounter;
	loaded = true;
	destroyed = false;
	referenceCount = 0;
	Resource::_idResourcesMap.insert(pair<int, Resource*>(id, this));
	released = true;
	lock = false;
	memorySize = 0;
	lastUseFrameCount = -1;
	//(ResourceManager.currentResourceManager) && (ResourceManager.currentResourceManager.addResource(this));
}


Resource::~Resource()
{
}

void Resource::activeResource(bool force) {
	lastUseFrameCount = Time::frame;
	if (!destroyed && loaded && (released || force))
		recreateResource();
}