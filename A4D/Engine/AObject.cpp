#include "stdafx.h"
#include "AObject.h"
int AObject::Instance = 0;
AObject::AObject(string n)
{
	name = n;
	instance = AObject::Instance;
	AObject::Instance++;
#if (EngineEditor)
	if (AObject::Instance >= INT_MAX)
	{
		//();
	}
#endif 
}
AObject::AObject()
{

}
AObject::~AObject()
{

}

void AObject::DestroyImmediate(AObject * Object)
{

}

void AObject::Destroy(AObject * Object)
{

}

int AObject::GetInstanceId()
{
	return instance;
}
