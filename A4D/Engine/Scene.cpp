#include "stdafx.h"
#include "Scene.h"
#include "EventDispatcher.h"
#include "SceneManager.h"
#include "GameWorld.h"
#include "TexturePool.h"
#include "WInputModel.h"
#include "Console.h"
#include "Pool.h"
#include "Time.h"
#include "MouseMgr.h"
#include "WGraphics.h"
#include "GameObject.h"
#include "Transform.h"
#include "../A4D.h"
Scene::Scene(string n)
{
	handle = AObject::Instance;
	AObject::Instance++;
	name = n;
	SceneManager::SetActiveScene(this);
#if (EngineEditor)
	HierarchyChangeEvent evt;
	evt.pComponent = NULL;
	evt.pScene = this;
	evt.transform = NULL;
	evt.type = AEventType::New;
	A4D::getInstance()->fire(EventId::HierarchyChanged, &evt);
#endif
}

Scene::~Scene()
{
}

void Scene::addChild(GameObject * gameObject)
{
	std::vector<GameObject*>::iterator iter = rootGameObjects.begin();
	if (iter == rootGameObjects.end())
	{
#if (EngineEditor)
		HierarchyChangeEvent evt;
		evt.pComponent = NULL;
		evt.pScene = this;
		evt.pGameObject = NULL;
		evt.transform = gameObject->transform;
		evt.type = AEventType::Add;
		A4D::getInstance()->fire(EventId::HierarchyChanged, &evt);
#endif
		rootGameObjects.push_back(gameObject);
		gameObject->m_pScene = this;
	}
}

void Scene::removeChild(GameObject * gameObject)
{
	std::vector<GameObject*>::iterator iter = rootGameObjects.begin();
	if (iter != rootGameObjects.end())
	{
#if (EngineEditor)
		HierarchyChangeEvent evt;
		evt.pComponent = NULL;
		evt.pScene = this;
		evt.transform = gameObject->transform;
		evt.type = AEventType::Remove;
		A4D::getInstance()->fire(EventId::HierarchyChanged, &evt);
#endif
		rootGameObjects.erase(iter);
	}
}

/**
*初始化八叉树。
*@param width 八叉树宽度。
*@param height 八叉树高度。
*@param depth 八叉树深度。
*@param center 八叉树中心点
*@param level 八叉树层级。
*/
//void Scene::initOctree(int width, int height, int depth, int center, int level) {
	//if (level == 0)
	//	level = 6;
	//this.treeSize = new D3DXVECTOR3(width, height, depth);
	//this.treeLevel = level;
	//this.treeRoot = new OctreeNode(this, 0);
	//this.treeRoot.init(center, this.treeSize);
//}

