#pragma once
class Layer
{
public:
	Layer();
	~Layer();
	static int _currentCameraCullingMask;//��ǰ��������Ӳ�����
	static int _visibleLayers;//��ǰlayer���Ӳ�����
	static bool isVisible(int mask);
	int mask;
	bool visible;//�ò��Ƿ�ɼ�
};

