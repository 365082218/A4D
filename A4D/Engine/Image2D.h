#pragma once
#include "Node.h"
//简单的2D图片绘制系统，仅支持基本的UI贴到窗口，直接用ID3DXSprite绘制

class Style
{
	float alpha;
	bool visible;
	int blendMode;
	int type;
};

class Image2D :
	public Node
{
public:
	Image2D();
	~Image2D();
	D3DXMATRIX transform;
	bool changed;
	//相对坐标系
	float x;
	float y;
	float width;
	float height;
	void updatePos();
	float xPos();
	float yPos();
	float _xPos;
	float _yPos;
	bool repaint;
	bool mouseEnable;//0:auto 1:mouseEnable=false,2:mouseEnabled=true
	int zOrder;//Z排序大覆盖小
	ID3DXSprite * pSprite;//图形绘制指针
	IDirect3DTexture9 * pTexture;//图片源
	D3DXIMAGE_INFO * pImageInfo;
	int renderType;//渲染模式
	bool optimizeScrollRect;
	bool mouseThrough;//鼠标穿透
	bool autoSize;//自动计算宽高
	bool hitTestPrior;//鼠标事件是优先检测自身还是子对象
	D3DVIEWPORT9 viewport;
	Style style;
	void destroy();
	void updateZOrder();
	void load(string tex);
	virtual void draw();
};

