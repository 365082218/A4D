#pragma once
#include <vector>
#include "RenderQueue.h"
#include "Render.h"
#include "EventDispatcher.h"
using namespace std;
class Render;
class RenderState;
class RenderQueue;
class Camera;
class DynamicBatchManager;
class BoundFrustum;
class EventDispatcher;
class Scene : public Node, public EventDispatcher
{
private:
public:
	Scene(string name = "");
	~Scene();
	int m_nBuildIndex;
	int m_nRootCount;
	bool m_bIsDirty;
	bool m_bIsLoaded;
	virtual void setParent(Node * parent);
	//D3DVECTOR treeSize;
	//int treeLevel;
	string m_path;
	string m_name;
	void updateScene();
	void render();
	void OnPreRender();
	void OnPostRender();
	void registerCamera(Camera * pCamera);
	void unregisterCamera(Camera * pCamera);
	void registerRender(Render * pRender);
	vector<Camera*> cameraPool;
	vector<Render*> renderPool;
	RenderState * state;
	void _preRenderScene(IDirect3DDevice9 * pDevice, RenderState * rs, BoundFrustum * pFrustum);
	void initOctree(int width, int height, int depth, int center, int level);
	vector<RenderQueue*> _quenes;
	vector<Render*> _cullingRenders;//在锥截
	int _cullingRendersLength;//在椎体内的物体列表长度
	DynamicBatchManager * _dynamicBatchManager;
	void addFrustumCullingObject(Render * renderObject);
	void removeFrustumCullingObject(Render * renderObject);
	void _clear(IDirect3DDevice9 * pDevice, RenderState * rs);
	void _renderScene(IDirect3DDevice9 * pDevice, RenderState * rs);
	void _postRenderUpdateComponents(RenderState * rs);
	RenderQueue* getRenderQueue(int index);
};

