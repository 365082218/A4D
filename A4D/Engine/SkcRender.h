#pragma once
#include "Render.h"
#include "RenderState.h"
#include "GeometryFilter.h"
#include "Material.h"
#include "SkcMeshFilter.h"
class SkcRender :public Render
{
	friend class GameObject;
public:
	SkcRender();
	~SkcRender();
	void Awake(GameObject * pOwner);
	void OnEnable(Event * pContext);
	void OnDisable(Event * pContext);
	void _render(RenderState * rs);
	//void OnMeshChanged(Event * pContext);
	//void _changeRenderObjectsByMesh();
	//void _changeRenderObjectByMesh(int index);

	vector<Material*> sharedMaterials;
	size_t type_id()
	{
		return typeid(SkcRender).hash_code();
	}
};