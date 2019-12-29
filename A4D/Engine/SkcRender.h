#pragma once
#include "Render.h"
class Material;
class RenderState;
class GameObject;
class SkcRender :public Render
{
	friend class GameObject;
public:
	SkcRender();
	~SkcRender();
	void Awake(GameObject * pOwner);
	void OnEnable(AEvent * pContext);
	void OnDisable(AEvent * pContext);
	void _render(RenderState * rs);
	vector<Material*> sharedMaterials;
	size_t type_id()
	{
		return typeid(SkcRender).hash_code();
	}
};