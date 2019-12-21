#include "AObject.h"
AObject::AObject(string n)
{
	name = n;
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
