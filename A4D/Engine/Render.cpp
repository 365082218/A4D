#include "stdafx.h"
#include "Render.h"
#include "Node.h"
#include "Component.h"
#include "EventDispatcher.h"
#include "GameObject.h"
#include "MeshFilter.h"
#include "BaseMesh.h"
#include "RenderState.h"
#include "Mesh.h"
#include "GeometryFilter.h"
#include "RenderElement.h"
Render::Render()
{
	_indexInSceneFrustumCullingObjects = 0;
}


Render::~Render()
{
}

void Render::Awake(GameObject * pOwner)
{
	__super::Awake(pOwner);
	this->meshFilter = (MeshFilter*)pOwner->getComponent(typeid(MeshFilter).hash_code());
}

//PV矩阵，摄像机视图AND投影矩阵的积
void Render::_renderUpdate(D3DXMATRIX * pMatrix)
{

}

void Render::OnMeshChanged(AEvent * context)
{
	if (meshFilter != NULL && meshFilter->_mesh->loaded)
	{
		_changeRenderObjectsByMesh();
	}
}

void Render::OnEnable(AEvent * context)
{
	if (context != NULL)
	{
		if (context->pComponent == this)
		{
			
		}
		else if (context->pComponent->type_id() == typeid(MeshFilter).hash_code())
		{
			if (this->meshFilter != NULL)
				this->meshFilter->offAll();
			this->meshFilter = dynamic_cast<MeshFilter*>(context->pComponent);
			if (this->meshFilter != NULL)
				this->meshFilter->on(EventId::MeshChanged, this, (LPHandler)&Component::OnMeshChanged, false);
		}
	}
}

void Render::OnDisable(AEvent * context)
{
	if (context != NULL)
	{
		if (context->pComponent == this)
		{
			
		}
		else if (context->pComponent->type_id() == typeid(MeshFilter).hash_code())
		{
			if (this->meshFilter != NULL)
				this->meshFilter->offAll();
			this->meshFilter = NULL;
		}
	}
}

void Render::_changeRenderObjectsByMesh()
{
	int renderElementsCount = meshFilter->_mesh->getRenderElementsCount();
	_renderElements.clear();
	for (int i = 0; i < renderElementsCount; i++)
	{
		_renderElements.push_back(NULL);
		_changeRenderObjectByMesh(i);
	}
}

void Render::_changeRenderObjectByMesh(int index)
{
	RenderElement * renderElement = _renderElements[index];
	if (renderElement == NULL)
		renderElement = _renderElements[index] = new RenderElement();// new SubMeshRenderElement();
	renderElement->render = this;
	//Material * material = sharedMaterials[index];
	//if (material == null)
	//	material = StandardMaterial.defaultMaterial;
	//(material) || (material = StandardMaterial.defaultMaterial);//如果无材质则使用标准默认材质
	BaseMesh * renderObj = meshFilter->_mesh->getRenderElement(index);
	//renderElement->_mainSortID = this._getSortID(renderObj, material);
	renderElement->gameobject = this->gameObject;
	renderElement->renderObj = renderObj;
	//renderElement->_material = material;
}