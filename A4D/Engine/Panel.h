#pragma once
#include "Image2D.h"
//��ͨ��ͷ������ק�����.
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
	//����һ��ui�ļ�
	void Load(string ui);
	void draw();
	float width;
	float height;
};

