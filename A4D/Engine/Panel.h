#pragma once
#include "Image2D.h"
//可通过头顶栏拖拽的面板.
class Panel :
	public Image2D
{
public:
	Panel();
	~Panel();
	void SetSize(float width, float height)
	{
		this->width = width;
		this->height = height;
	}
	//加载一个ui文件
	void Load(string ui);
	void draw();
	float width;
	float height;
};

