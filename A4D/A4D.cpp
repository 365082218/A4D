#include "A4D.h"
A4D * A4D::_Instance = NULL;
A4D::A4D(QWidget *parent)
	: QMainWindow(parent)
{
	A4D::_Instance = this;
	EditorPlaying = false;
	pTexturePool = new TexturePool();
	pGraphs = new WGraphics();
	
	ui.setupUi(this);
	if (!pGraphs->Init(ui.editorWindow->width(), ui.editorWindow->height(), (HWND)ui.editorWindow->winId(), false))
		return;
	setFocusPolicy(Qt::WheelFocus); // 允许按键时间 ...
	setMouseTracking(true); // 允许鼠标移动 ...
	pInput = new InputMgr();
	pConsole = new Console();
	pTime = new Time();
	pMouse = new MouseMgr();
	pInput->Init();
	pGraphs->Setup();
	pWorld = new GameWorld();
}

A4D::~A4D()
{
	A4D::_Instance = this;
}

void A4D::EngineRender()
{
	pTime->deltaTime = 0.02f;
	pTime->update();
	pMouse->update();
	EditorUpdate(); //编辑器刷新帧.
}

//void A4D::paintEvent(QPaintEvent *event)
//{
//	//计算fps
//	//frameCount++;
//	//if (getTime() > 1.0f)
//	//{
//	//	fps = frameCount;
//	//	frameCount = 0;
//	//	startFPStimer();
//	//	//设置父窗口标题显示fps值
//	//	parentWidget()->setWindowTitle("FPS: " + QString::number(fps));
//	//}
//	//frameTime = getFrameTime();
//	////更新场景和渲染场景
//	//UpdateScene(frameTime);
//	//RenderScene();
//
//
//	QWidget::paintEvent(event);
//}

void A4D::EditorUpdate()
{
	pGraphs->EditorUpdate();
	if (EditorPlaying)
	{
		pGraphs->Loop();
	}
}

bool A4D::event(QEvent * event)
{
	QKeyEvent *ke = dynamic_cast<QKeyEvent*>(event);
	int t = event->type();
	switch (event->type())
	{
	case QEvent::KeyPress:
		pInput->OnKeyDown(ke->nativeVirtualKey());
		break;
	default:
		break;
	}
	return QWidget::event(event);
}