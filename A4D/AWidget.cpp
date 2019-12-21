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
	//����fps
	//frameCount++;
	//if (getTime() > 1.0f)
	//{
	//	fps = frameCount;
	//	frameCount = 0;
	//	startFPStimer();
	//	//���ø����ڱ�����ʾfpsֵ
	//	parentWidget()->setWindowTitle("FPS: " + QString::number(fps));
	//}
	//frameTime = getFrameTime();
	////���³�������Ⱦ����
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