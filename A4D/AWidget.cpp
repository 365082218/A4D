#include "Engine/stdafx.h"
#include "Engine/Node.h"
#include "Engine/BoundFrustum.h"
#include "Engine/Pool.h"
#include "Engine/Vector3.h"
#include "Engine/Time.h"
#include "Engine/EventDispatcher.h"
#include "Engine/resources.h"
#include "Engine/Component.h"
#include "Engine/Scene.h"
#include "Engine/Layer.h"
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
#include "AWidget.h"
#include "A4D.h"
AWidget::AWidget(QWidget * parent) :QWidget(parent)
{
	setAttribute(Qt::WA_PaintOnScreen, true);
}

QPaintEngine * AWidget::paintEngine() const
{
	return NULL;
}
void AWidget::paintEvent(QPaintEvent *event)
{
	//计算fps
	//frameCount++;
	//if (getTime() > 1.0f)
	//{
	//	fps = frameCount;
	//	frameCount = 0;
	//	startFPStimer();
	//	//设置父窗口标题显示fps值
	//	parentWidget()->setWindowTitle("FPS: " + QString::number(fps));
	//}
	//frameTime = getFrameTime();
	////更新场景和渲染场景
	//UpdateScene(frameTime);
	//RenderScene();
	A4D::getInstance()->EngineRender();
	update();
	QWidget::paintEvent(event);
}

bool AWidget::event(QEvent * event)
{
	QKeyEvent *ke = dynamic_cast<QKeyEvent*>(event);
	int t = event->type();
	switch (event->type())
	{
	case QEvent::KeyPress:
		A4D::getInstance()->pInput->OnKeyDown(ke->nativeScanCode());
		break;
	default:
		break;
	}
	return QWidget::event(event);
}