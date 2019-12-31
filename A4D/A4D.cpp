#include "Engine/stdafx.h"
//被其他类依赖，却不依赖其他类的
#include "Engine/Node.h"
#include "Engine/BoundFrustum.h"
#include "Engine/Pool.h"
#include "Engine/Vector3.h"
#include "Engine/Time.h"
#include "Engine/EventDispatcher.h"
#include "Engine/resources.h"
#include "Engine/Component.h"
#include "Engine/Scene.h"
#include "Engine/GameObject.h"
#include "Engine/StaticBatch.h"
#include "Engine/RenderElement.h"
#include "Engine/BoundBox.h"
#include "Engine/BoundSphere.h"
#include "Engine/BaseMesh.h"
#include "Engine/RenderState.h"
#include "Engine/RenderTexture.h"
#include "Engine/BoundFrustum.h"
#include "Engine/Camera.h"
#include "Engine/WGraphics.h"
#include "Engine/Image2D.h"
#include "Engine/Button.h"
#include "Engine/Panel.h"
#include "Engine/MainUi.h"
#include "Engine/GameWorld.h"
#include "Engine/TexturePool.h"
#include "Engine/WInputModel.h"
#include "Engine/Console.h"
#include "Engine/Time.h"
#include "Engine/MouseMgr.h"
#include "Engine/Transform.h"
#include "Engine/Render.h"
#include "Engine/GeometryFilter.h"
#include "Engine/MeshFilter.h"
#include "Engine/Mesh.h"
#include "Engine/MaterialUnit.h"
#include "Engine/BoneWeight.h"
#include "Engine/SubMesh.h"
#include "Engine/SkcRender.h"
#include "A4D.h"

extern void RegisterCrashHandler();
//缺少Log模块
//缺少Lua模块
//缺少崩溃捕捉模块
//缺少protobuf模块
//缺少kcp模块

#if defined (_LOG4CPP)
log4cpp::Category* main_log = &log4cpp::Category::getInstance("log");
void LogInit()
{
	//1. 初始化Layout对象
	log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout();
	pLayout->setConversionPattern("%d: %p %c %x: %m%n");
	// 2. 初始化一个appender 对象    
	log4cpp::Appender* appender = new log4cpp::FileAppender("FileAppender", "./gamesvr.log");
	// 3. 把layout对象附着在appender对象上    
	appender->setLayout(pLayout);
	// 5. 设置additivity为false，替换已有的appender           
	main_log->setAdditivity(false);
	// 5. 把appender对象附到category上    
	main_log->setAppender(appender);
	// 6. 设置category的优先级，低于此优先级的日志不被记录    
	main_log->setPriority(log4cpp::Priority::DEBUG);
}
#endif

A4D * A4D::_Instance = NULL;
A4D::A4D(QWidget *parent)
	: QMainWindow(parent)
{
	RegisterCrashHandler();
#if defined(_LOG4CPP)
	LogInit();
#endif

	//*(int*)0 = 1;
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
	pWorld = new GameWorld();
	InitListener();//监听编辑器场景发生变化
	InitHandler();
	pGraphs->Setup();
}

A4D::~A4D()
{
	A4D::_Instance = NULL;
	delete pTexturePool;
}

void A4D::OnEnable(AEvent * context)
{
	if (context->pComponent != NULL)
	{
		size_t hash = context->pComponent->type_id();
		if (hash == typeid(Camera).hash_code())
		{
			this->pGraphs->RegisterCamera((Camera*)context->pComponent);
		}
		else if (hash == typeid(SkcRender).hash_code())
		{
			this->pGraphs->addFrustumCullingObject((Render*)context->pComponent);
		}
	}
}

void A4D::OnDisable(AEvent * context)
{
	if (context->pComponent != NULL)
	{
		int hash = context->pComponent->type_id();
		if (hash == typeid(Camera).hash_code())
		{
			this->pGraphs->UnregisterCamera((Camera*)context->pComponent);
		}
		else if (hash == typeid(Render).hash_code())
		{
			this->pGraphs->removeFrustumCullingObject((Render*)context->pComponent);
		}
	}
}

void A4D::InitListener()
{
	on(EventId::HierarchyChanged, this, (LPHandler)&EventDispatcher::OnHierarchyChanged, false);
	on(EventId::ComponentEnable, this, (LPHandler)&EventDispatcher::OnEnable, false);
	on(EventId::ComponentDisable, this, (LPHandler)&EventDispatcher::OnDisable, false);
}

void A4D::OnHierarchyChanged(AEvent * evt)
{
	HierarchyChangeEvent * p = (HierarchyChangeEvent*)evt;
	if (p->type == AEventType::Add)
	{
		//最顶层加
		if (p->pScene != NULL)
		{
			int instance = p->pScene->handle;
			//map<int, Transform*>::iterator iter = TransformHash.find(instance);
			map<int, QTreeWidgetItem *>::iterator iter = TreeItemHash.find(instance);
			if (iter != TreeItemHash.end())
			{
				//找到了.
				//被add的对象可能存在
				//iter->second->addChild();
				//this->ui.treeWidget->insertTopLevelItem();
			}
			else
			{

			}
		}
		else
		{

		}
	}
	else if (p->type == AEventType::Remove)
	{

	}
	else if (p->type == AEventType::New)
	{
		//顶层添加对象，一定是场景.
		map<int, QTreeWidgetItem *>::iterator iter = TreeItemHash.find(p->pScene->handle);
		if (iter != TreeItemHash.end())
		{
			//找到了，已经存在此场景，什么也不做，逻辑上不可能到这里
		}
		else
		{
			QTreeWidgetItem * pItem = new QTreeWidgetItem(QStringList(p->pScene->name.c_str()));
			this->ui.treeWidget->addTopLevelItem(pItem);
			TreeItemHash.insert(pair<int, QTreeWidgetItem*>(p->pScene->handle, pItem));
		}
	}
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

void A4D::ChangePlaying(bool play)
{
	EditorPlaying = play;
	if (play)
		pGraphs->InitGameDevice();
	else
	{
		pGraphs->ReleaseGameDevice();
	}
}