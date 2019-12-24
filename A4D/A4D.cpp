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
	InitHandler();
}

A4D::~A4D()
{
	A4D::_Instance = NULL;
	delete pTexturePool;

}

void A4D::InitHandler()
{
	QObject::connect(ui.actionShaded, &QAction::triggered, this, &A4D::Shaded);
	QObject::connect(ui.actionWireframe, &QAction::triggered, this, &A4D::WireFrame);
}

void A4D::WireFrame(bool trigger)
{
	OutputDebugStringA("");
	if (pGraphs != NULL && pGraphs->pEditorDevice != NULL)
	{
		pGraphs->pEditorDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);//线框
	}
}

void A4D::Shaded(bool trigger)
{
	if (pGraphs != NULL && pGraphs->pEditorDevice != NULL)
	{
		pGraphs->pEditorDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);//面
	}
}

void A4D::EngineRender()
{
	pTime->deltaTime = 0.02f;
	pTime->update();
	pMouse->update();
	EditorUpdate(); //编辑器刷新帧.
}

void A4D::paintEvent(QPaintEvent *event)
{
	this->ui.treeWidget->clear();
	this->ui.treeWidget->insertTopLevelItem(0, new QTreeWidgetItem(this->ui.treeWidget, QStringList("123")));
	this->ui.treeWidget->insertTopLevelItem(0, new QTreeWidgetItem(this->ui.treeWidget, QStringList("234")));
	this->ui.treeWidget->insertTopLevelItem(0, new QTreeWidgetItem(this->ui.treeWidget, QStringList("456")));
	this->ui.treeWidget->insertTopLevelItem(0, new QTreeWidgetItem(this->ui.treeWidget, QStringList("789")));
	this->ui.treeWidget->insertTopLevelItem(0, new QTreeWidgetItem(this->ui.treeWidget, QStringList("111")));
	QWidget::paintEvent(event);
}

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