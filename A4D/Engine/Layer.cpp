#include "stdafx.h"
#include "Layer.h"

int Layer::_currentCameraCullingMask = 0;//��ǰ��������Ӳ�mask
int Layer::_visibleLayers = 0;
Layer::Layer()
{
}


Layer::~Layer()
{
}

bool Layer::isVisible(int mask)
{
	return true;
	//return (mask & Layer::_currentCameraCullingMask & Layer::_visibleLayers) != 0;
}