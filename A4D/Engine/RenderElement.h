#pragma once
class BaseMaterial;
class StaticBatch;
class RenderElement
{
public:
	RenderElement();
	~RenderElement();
	BaseMaterial * _material;
	StaticBatch * _staticBatch;
	Render * render;
	BaseMesh * renderObj;
	bool _canDynamicBatch;
	GameObject * gameobject;
	int type;//1��ͨ 2��̬����

};