#include "stdafx.h"
#include "Image2D.h"
#include "Mesh.h"
#include "BaseMesh.h"
#include "W4DCommon.h"
#include "RenderState.h"
#include "Node.h"
#include "Component.h"
#include "EventDispatcher.h"
#include "resources.h"
#include "GameWorld.h"
#include "GameObject.h"
#include "Transform.h"
#include "TexturePool.h"
#include "Camera.h"
#include "../A4D.h"
#include "WInputModel.h"
#include "Console.h"
#include "Pool.h"
#include "Time.h"
#include "MouseMgr.h"
#include "WGraphics.h"

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
	mouseThrough = false;//鼠标穿透
	autoSize = true;
	hitTestPrior = false;
	memset(&viewport, 0, sizeof(viewport));
	memset(&style, 0, sizeof(style));
}


Image2D::~Image2D()
{
}

//释放此图片使用的贴图资源
void Image2D::destroy()
{
	A4D::getInstance()->pTexturePool->recover(pTexture);
	pTexture = NULL;
	pImageInfo = NULL;
}

//更新子控件的Z排序
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

//计算相对父节点的x轴偏移
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