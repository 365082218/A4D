#include "stdafx.h"
#include "Image2D.h"
#include "TexturePool.h"

Image2D::Image2D()
{
	pTexture = NULL;
	pImageInfo = NULL;
	changed = false;
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	repaint = false;
	mouseEnable = true;
	zOrder = 1;
	pSprite = NULL;
	pTexture = NULL;
	renderType = 0;
	optimizeScrollRect = false;
	mouseThrough = false;//��괩͸
	autoSize = true;
	hitTestPrior = false;
	memset(&viewport, 0, sizeof(viewport));
	memset(&style, 0, sizeof(style));
}


Image2D::~Image2D()
{
}

//�ͷŴ�ͼƬʹ�õ���ͼ��Դ
void Image2D::destroy()
{
	A4D::getInstance()->pTexturePool->recover(pTexture);
	pTexture = NULL;
	pImageInfo = NULL;
}

//�����ӿؼ���Z����
void Image2D::updateZOrder()
{

}

void Image2D::load(string tex)
{
	A4D::getInstance()->pTexturePool->getItem(tex, &pTexture, &pImageInfo);
	if (pImageInfo != NULL)
	{
		width = pImageInfo->Width;
		height = pImageInfo->Height;
	}
	repaint = true;
}

void Image2D::draw()
{
	updatePos();
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.bottom = height;
	rc.right = width;
	A4D::getInstance()->Graphics()->pSprite->Draw(this->pTexture,  &rc, NULL, &D3DXVECTOR3(_xPos, _yPos, 0), 0xFFFFFFFF);
}

//������Ը��ڵ��x��ƫ��
float Image2D::xPos()
{
	updatePos();
	return _xPos;
}

float Image2D::yPos()
{
	updatePos();
	return _yPos;
}

void Image2D::updatePos()
{
	if (repaint)
	{
		Node * p = (this->m_pParent);
		Image2D * img = (Image2D*)p;
		float x = this->x; float y = this->y;
		while (p != NULL)
		{
			img = (Image2D*)p;
			x += img->x;
			y += img->y;
			p = p->m_pParent;
		}
		_xPos = x;
		_yPos = y;
	}
}