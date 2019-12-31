#pragma once
class Scene;
class Camera;
class GameObject;
class StaticBatch;
class RenderElement;
class RenderState
{
public:
	RenderState();
	~RenderState();
	StaticBatch * _staticBatch = NULL;
	int _batchIndexStart;
	int _batchIndexEnd = 0;
	D3DXMATRIX _viewMatrix;
	D3DXMATRIX _projectionMatrix;
	D3DXMATRIX _projectionViewMatrix;
	D3DVIEWPORT9 _viewport;
	//_shader = null;
	/**距上一帧间隔时间。*/
	float elapsedTime;
	/**当前场景。*/
	Scene * scene = NULL;
	/**当前渲染3D精灵。*/
	GameObject * owner = NULL;
	/**当前渲染物体。*/
	RenderElement * renderElement = NULL;
	/**当前摄像机。*/
	Camera * camera = NULL;

	IDirect3DDevice9 * pDevice;//设备
};

