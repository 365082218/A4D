#pragma once
class RenderQueue;
class DynamicBatchManager;
class Scene;
class Camera;
class RenderState;
class BoundFrustum;
class Render;
class WGraphics
{
public:
	WGraphics();
	~WGraphics();
	//��ʼ���༭������
	bool Init(int width, int height, HWND hWnd, bool fullscreen);
	//��ʼ����Ϸ���л���
	void InitGameDevice();
	void ReleaseGameDevice();
	void EditorUpdate();
	void Loop();
	void ShutDown();
	void Setup();
	int width;
	int height;
	ID3DXSprite * pSprite;
	IDirect3D9 * pD3d9;
	IDirect3DDevice9 * pEditorDevice;//�༭���豸
	IDirect3DDevice9 * pGameDevice;//��ʽ��Ϸ�����豸
	vector<Scene*> pScene;
	Camera* pEditCamera;//�������
	void LoadSkc(char * file);
	void RegisterCamera(Camera * pCamera);
	void UnregisterCamera(Camera * pCamera);
	void RegisterRender(Render * pRender);
	//void RegisterRender(Render * pRender);
	void Draw();
	vector<Camera*> cameraPool;
	vector<Render*> renderPool;
	RenderState * state;
	void UpdateGameObject();

	vector<RenderQueue*> _quenes;
	vector<Render*> _cullingRenders;//��׶��
	int _cullingRendersLength;//��׵���ڵ������б���
	DynamicBatchManager * _dynamicBatchManager;
	void addFrustumCullingObject(Render * renderObject);
	void removeFrustumCullingObject(Render * renderObject);
	void _clear(IDirect3DDevice9 * pDevice, RenderState * rs);
	void _renderScene(IDirect3DDevice9 * pDevice, RenderState * rs);
	void _postRenderUpdateComponents(RenderState * rs);
	RenderQueue* getRenderQueue(int index);
	void _preRenderScene(IDirect3DDevice9 * pDevice, RenderState * rs, BoundFrustum * pFrustum);
private:
};

