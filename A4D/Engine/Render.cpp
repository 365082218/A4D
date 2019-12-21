#include "stdafx.h"
#include "Render.h"
#include "MeshFilter.h"
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

void Render::OnMeshChanged(Event * context)
{
	if (meshFilter != NULL && meshFilter->_mesh->loaded)
	{
		_changeRenderObjectsByMesh();
	}
}

void Render::OnEnable(Event * context)
{
	if (context != NULL)
	{
		if (context->psender == this)
			gameObject->m_pScene->addFrustumCullingObject(this);
		else if (context->psender->type_id() == typeid(MeshFilter).hash_code())
		{
			if (this->meshFilter != NULL)
				this->meshFilter->offAll();
			this->meshFilter = (MeshFilter*)context->psender;
			if (this->meshFilter != NULL)
				this->meshFilter->on(EventId::MeshChanged, this, (LPHandler)&Component::OnMeshChanged, NULL, false);
		}
	}
}

void Render::OnDisable(Event * context)
{
	if (context != NULL)
	{
		if (context->psender == this)
			gameObject->m_pScene->removeFrustumCullingObject(this);
		else if (context->psender->type_id() == typeid(MeshFilter).hash_code())
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