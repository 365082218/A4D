#include "stdafx.h"
#include "Component.h"
#include "EventDispatcher.h"
#include "Node.h"
#include "Render.h"
#include "SkcRender.h"
#include "RenderState.h"
#include "Transform.h"
#include "GameObject.h"
#include "Scene.h"
#include "MeshFilter.h"
#include "SkcMeshFilter.h"
#include "BaseMaterial.h"
#include "Material.h"
#include "RenderElement.h"
#include "StaticBatch.h"
#include "RenderQueue.h"
#include "RenderTexture.h"
#include "BoundFrustum.h"
#include "DynamicBatchManager.h"
#include "WGraphics.h"
#include "Camera.h"
#include "BoundBox.h"
#include "BoundSphere.h"
#include "Pool.h"
#include "Time.h"
#include "resources.h"
#include "Vector3.h"
#include "BaseMesh.h"

REGISTER_CLASS(SkcRender)
SkcRender::SkcRender()
{

}

SkcRender::~SkcRender()
{
}

void SkcRender::Awake(GameObject * pOwner)
{
	__super::Awake(pOwner);
	this->meshFilter = (SkcMeshFilter*)pOwner->getComponent(typeid(SkcMeshFilter).hash_code());
}

//相关组件激活
void SkcRender::OnEnable(AEvent * context)
{
	__super::OnEnable(context);
	if (context != NULL)
	{
		if (context->pComponent->type_id() == typeid(SkcMeshFilter).hash_code())
		{
			if (this->meshFilter != NULL)
				this->meshFilter->offAll();
			this->meshFilter = dynamic_cast<SkcMeshFilter*>(context->pComponent);
			if (this->meshFilter != NULL)
				this->meshFilter->on(EventId::MeshChanged, (EventDispatcher*)this, (LPHandler)&EventDispatcher::OnMeshChanged, false);
		}
	}
}

//相关组件关闭/卸载
void SkcRender::OnDisable(AEvent * context)
{
	__super::OnDisable(context);
	if (context != NULL)
	{
		if (context->pComponent->type_id() == typeid(SkcMeshFilter).hash_code())
		{
			if (this->meshFilter != NULL)
				this->meshFilter->offAll();
			this->meshFilter = NULL;
		}
	}
}

void SkcRender::_render(RenderState * rs)
{

}

//void SkcRender::OnMeshChanged(Event * pContext)
//{
//	__super::OnMeshChanged(pContext);
//}

//void SkcRender::_changeRenderObjectsByMesh()
//{
//	int renderElementsCount = meshFilter->_mesh->getRenderElementsCount();
//	_renderElements.clear();
//	for (int i = 0; i < renderElementsCount; i++)
//	{
//		_renderElements.push_back(null);
//		_changeRenderObjectByMesh(i);
//	}
//}
//
//void SkcRender::_changeRenderObjectByMesh(int index)
//{
//	RenderElement * renderElement = _renderElements[index];
//	if (renderElement == null)
//		renderElement = _renderElements[index] = new RenderElement();// new SubMeshRenderElement();
//	renderElement->render = this;
//	//Material * material = sharedMaterials[index];
//	//if (material == null)
//	//	material = StandardMaterial.defaultMaterial;
//	//(material) || (material = StandardMaterial.defaultMaterial);//如果无材质则使用标准默认材质
//	BaseMesh * renderObj = meshFilter->_mesh->getRenderElement(index);
//	//renderElement->_mainSortID = this._getSortID(renderObj, material);
//	renderElement->gameobject = this->gameObject;
//	renderElement->renderObj = renderObj;
//	//renderElement->_material = material;
//}