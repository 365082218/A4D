#include "Engine/stdafx.h"
#include "A4D.h"
#include <QtWidgets/QApplication>
#include "Engine/W4DCommon.h"
#include "Engine/Node.h"
#include "Engine/Component.h"
#include "Engine/Transform.h"
#include "Engine/GameObject.h"
#include "Engine/global.h"
#include "Engine/WGraphics.h"
#include "Engine/TexturePool.h"
#include "Engine/GameWorld.h"
#include "Engine/Console.h"
#include "Engine/WInputModel.h"
#include "Engine/MouseMgr.h"
#include "Engine/Pool.h"
#include "Engine/Time.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	A4D w;
	w.show();
	return a.exec();
}
