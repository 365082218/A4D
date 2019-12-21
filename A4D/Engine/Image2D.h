#pragma once
#include "Node.h"
//�򵥵�2DͼƬ����ϵͳ����֧�ֻ�����UI�������ڣ�ֱ����ID3DXSprite����

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
	//�������ϵ
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
	int zOrder;//Z����󸲸�С
	ID3DXSprite * pSprite;//ͼ�λ���ָ��
	IDirect3DTexture9 * pTexture;//ͼƬԴ
	D3DXIMAGE_INFO * pImageInfo;
	int renderType;//��Ⱦģʽ
	bool optimizeScrollRect;
	bool mouseThrough;//��괩͸
	bool autoSize;//�Զ�������
	bool hitTestPrior;//����¼������ȼ���������Ӷ���
	D3DVIEWPORT9 viewport;
	Style style;
	void destroy();
	void updateZOrder();
	void load(string tex);
	virtual void draw();
};

