#include "stdafx.h"
#include "Layer.h"

int Layer::_currentCameraCullingMask = 0;//当前摄像机可视层mask
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