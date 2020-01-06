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

void A4D::InitHandler()
{
	QObject::connect(ui.actionShaded, &QAction::triggered, this, &A4D::Shaded);
	QObject::connect(ui.actionWireframe, &QAction::triggered, this, &A4D::WireFrame);
	QObject::connect(ui.treeWidget, &QWidget::customContextMenuRequested, this, &A4D::ShowMyContextMenu);
}

void A4D::OnHierarchyChanged(AEvent * evt)
{
	HierarchyChangeEvent * p = (HierarchyChangeEvent*)evt;
	if (p->type == AEventType::Add)
	{
		if (p->pGameObject == NULL)
		{
			//场景下添加对象.
			int instance = p->pScene->handle;
			map<int, QTreeWidgetItem *>::iterator iter = ItemHash.find(instance);
			if (iter != ItemHash.end())
			{
				//找到了.
				//被add的对象可能存在
				QTreeWidgetItem * pItem = new QTreeWidgetItem(QStringList(p->transform->gameObject->name.c_str()));
				iter->second->addChild(pItem);
				ItemHash.insert(pair<int, QTreeWidgetItem*>(p->transform->gameObject->GetInstanceId(), pItem));
				TreeHash.insert(pair<QTreeWidgetItem*, int>(pItem, p->transform->gameObject->GetInstanceId()));
				GameObjectHash.insert(pair<int, GameObject*>(p->transform->gameObject->GetInstanceId(), p->transform->gameObject));
			}
			else
			{
				//没找到,出错了
			}
		}
		else
		{
			//对象下添加对象
			map<int, QTreeWidgetItem *>::iterator iter = ItemHash.find(p->pGameObject->GetInstanceId());
			if (iter != ItemHash.end())
			{
				//找到了.
				QTreeWidgetItem * pItem = new QTreeWidgetItem(QStringList(p->transform->gameObject->name.c_str()));
				iter->second->addChild(pItem);
				ItemHash.insert(pair<int, QTreeWidgetItem*>(p->transform->gameObject->GetInstanceId(), pItem));
				TreeHash.insert(pair<QTreeWidgetItem*, int>(pItem, p->transform->gameObject->GetInstanceId()));
				GameObjectHash.insert(pair<int, GameObject*>(p->transform->gameObject->GetInstanceId(), p->transform->gameObject));
			}
			else
			{
				//没找到,出错了
				
			}

		}
	}
	else if (p->type == AEventType::Remove)
	{

	}
	else if (p->type == AEventType::New)
	{
		//顶层添加对象，一定是场景.
		map<int, QTreeWidgetItem *>::iterator iter = ItemHash.find(p->pScene->handle);
		if (iter != ItemHash.end())
		{
			//找到了，已经存在此场景，什么也不做，逻辑上不可能到这里
		}
		else
		{
			QTreeWidgetItem * pItem = new QTreeWidgetItem(QStringList(p->pScene->name.c_str()));
			this->ui.treeWidget->addTopLevelItem(pItem);
			ItemHash.insert(pair<int, QTreeWidgetItem*>(p->pScene->handle, pItem));
			TreeHash.insert(pair<QTreeWidgetItem*, int>(pItem, p->pScene->handle));
			SceneHash.insert(pair<int, Scene*>(p->pScene->handle, p->pScene));
		}
	}
}

void A4D::Delete()
{
	::MessageBox(NULL, _T("Delete"), _T(""), MB_OK);
}

void A4D::Duplicate()
{
	::MessageBox(NULL, _T("Duplicate"), _T(""), MB_OK);
}

void A4D::Rename()
{
	::MessageBox(NULL, _T("Rename"), _T(""), MB_OK);
}

void A4D::PasteObject()
{
	::MessageBox(NULL, _T("PasteObject"), _T(""), MB_OK);
}

void A4D::CopyObject()
{
	::MessageBox(NULL, _T("CopyObject"), _T(""), MB_OK);
}

void A4D::ShowMyContextMenu(QPoint point)
{
	//! 创建右键菜单
	QMenu menu;
	QTreeWidgetItem * item = ui.treeWidget->currentItem();
	if (item == NULL)
	{
		//空白处的菜单
		QList<QTreeWidgetItem*> list = ui.treeWidget->selectedItems();
		if (list.size() == 1)
		{
			//ShowMyContextMenuAtItem(list[0]);//如果是预设.显示的菜单
			::MessageBox(NULL, _T("ShowMyContextMenuAtItem"), _T(""), MB_OK);
		}
		else
		{
			//ShowMyDefaultContextMenu();//一个都没选择/或者选择多个.
			::MessageBox(NULL, _T("ShowMyDefaultContextMenu"), _T(""), MB_OK);
		}
	}
	else
	{
		map<QTreeWidgetItem *, int>::iterator it = TreeHash.find(item);
		if (it != TreeHash.end())
		{
			map<int, Scene*>::iterator iterScene = SceneHash.find(it->second);
			if (iterScene != SceneHash.end())
			{
				//选择项是一个场景
				QAction* action1 = new QAction(&menu);
				action1->setObjectName("Set Active Scene");
				action1->setText(tr("Set Active Scene"));
				menu.addAction(action1);
			}
			else
			{
				//选择项是一个游戏对象
				map<int, GameObject*>::iterator iterGameObject = GameObjectHash.find(it->second);
				if (iterGameObject != GameObjectHash.end())
				{
					//第一组
					QAction* action1 = new QAction(&menu);
					action1->setObjectName("Copy");
					action1->setText(tr("Copy"));
					menu.addAction(action1);

					QObject::connect(action1, &QAction::triggered, this, &A4D::CopyObject);

					QAction* action2 = new QAction(&menu);
					action2->setObjectName("Paste");
					action2->setText(tr("Paste"));
					menu.addAction(action2);

					QObject::connect(action2, &QAction::triggered, this, &A4D::PasteObject);

					menu.addSeparator();
					//第二组 重命名 duplicate 删除
					QAction* action3 = new QAction(&menu);
					action3->setObjectName("Rename");
					action3->setText(tr("Rename"));
					menu.addAction(action3);
					QObject::connect(action3, &QAction::triggered, this, &A4D::Rename);

					QAction* action4 = new QAction(&menu);
					action4->setObjectName("Duplicate");
					action4->setText(tr("Duplicate"));
					menu.addAction(action4);
					QObject::connect(action4, &QAction::triggered, this, &A4D::Duplicate);

					QAction* action5 = new QAction(&menu);
					action5->setObjectName("Delete");
					action5->setText(tr("Delete"));
					menu.addAction(action5);
					QObject::connect(action5, &QAction::triggered, this, &A4D::Delete);
					
					//如果是关联到预设-增加一组预设菜单
					//最后一组普通菜单.
					//QAction * action6 = new QAction(&action5);
				}
			}
		}
	}
	//! 添加右键菜单中的action
	//! 例如添加 action1
	
	//! 显示该菜单，进入消息循环
	menu.exec(ui.treeWidget->mapToGlobal(point)/*全局位置*/);
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