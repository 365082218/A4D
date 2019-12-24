#pragma once

#include <QtWidgets/QMainWindow>
#include <QtGui/qevent.h>
#include "ui_A4D.h"

#include <d3d9.h>
#include <mmsystem.h>
#include <d3dx9core.h>
#include "./Engine/WGraphics.h"
#include "./Engine/WInputModel.h"
#include "Engine/GameWorld.h"
#include "Engine/TexturePool.h"
#include "Engine/Console.h"
#include "Engine/Time.h"
#include "Engine/MouseMgr.h"
class InputMgr;
class Mesh;
class Camera;
class Scene;
class GameWorld;
class TexturePool;
class Console;
class Time;
class MouseMgr;
class A4D : public QMainWindow
{
	Q_OBJECT

public:
	A4D(QWidget *parent = Q_NULLPTR);
	~A4D();
	static A4D * _Instance;
	static A4D * getInstance()
	{
		return _Instance;
	}
	static int width() {
		return A4D::_Instance->ui.editorWindow->width();
	}
	static int height()
	{
		return A4D::_Instance->ui.editorWindow->height();
	}
	static HWND window()
	{
		return (HWND)A4D::_Instance->ui.editorWindow->winId();
	}
	//ID3DXSprite * pSprite;
	//IDirect3D9 * pD3d9;
	//IDirect3DDevice9 * pDevice;//编辑器设备
	//IDirect3DDevice9 * pGameDevice;//正式游戏环境设备
	unsigned long frameCnt;
	Scene * pEditScene;
	Camera * pEditCamera;
	WGraphics * Graphics() { return pGraphs; };
	WGraphics * pGraphs;
	GameWorld * pWorld;
	TexturePool * pTexturePool;
	InputMgr * pInput;
	Console * pConsole;
	Time * pTime;
	MouseMgr * pMouse;
	bool EditorPlaying;
	void EditorUpdate();
	void ChangePlaying(bool play)
	{
		EditorPlaying = play;
		if (play)
			pGraphs->InitGameDevice();
		else
		{
			pGraphs->ReleaseGameDevice();
		}
	}
	void EngineRender();
	void InitHandler();
	void WireFrame(bool b);
	void Shaded(bool trigger);
	bool event(QEvent *);
	void paintEvent(QPaintEvent *event);
private:
	Ui::A4DClass ui;
};
