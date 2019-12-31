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
	/**����һ֡���ʱ�䡣*/
	float elapsedTime;
	/**��ǰ������*/
	Scene * scene = NULL;
	/**��ǰ��Ⱦ3D���顣*/
	GameObject * owner = NULL;
	/**��ǰ��Ⱦ���塣*/
	RenderElement * renderElement = NULL;
	/**��ǰ�������*/
	Camera * camera = NULL;

	IDirect3DDevice9 * pDevice;//�豸
};

