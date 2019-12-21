#pragma once

#include <d3d9.h>
#include <mmsystem.h>

class Mesh;
class Camera;
class Scene;
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
	ID3DXSprite * pSprite;
	IDirect3D9 * pD3d9;
	IDirect3DDevice9 * pEditorDevice;//�༭���豸
	IDirect3DDevice9 * pGameDevice;//��ʽ��Ϸ�����豸
	unsigned long frameCnt;
	Scene * pEditScene;
	Camera * pEditCamera;
	void LoadSkc(char * file);
private:
};

