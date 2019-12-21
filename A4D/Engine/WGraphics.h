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
	//初始化编辑器环境
	bool Init(int width, int height, HWND hWnd, bool fullscreen);
	//初始化游戏运行环境
	void InitGameDevice();
	void ReleaseGameDevice();
	void EditorUpdate();
	void Loop();
	void ShutDown();
	void Setup();
	ID3DXSprite * pSprite;
	IDirect3D9 * pD3d9;
	IDirect3DDevice9 * pEditorDevice;//编辑器设备
	IDirect3DDevice9 * pGameDevice;//正式游戏环境设备
	unsigned long frameCnt;
	Scene * pEditScene;
	Camera * pEditCamera;
	void LoadSkc(char * file);
private:
};

