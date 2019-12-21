#pragma once
class Layer
{
public:
	Layer();
	~Layer();
	static int _currentCameraCullingMask;//当前摄像机可视层掩码
	static int _visibleLayers;//当前layer可视层掩码
	static bool isVisible(int mask);
	int mask;
	bool visible;//该层是否可见
};

