#include "stdafx.h"
#include "Image2D.h"
#include "Panel.h"
#include "MainUi.h"
#include "Node.h"
MainUi::MainUi()
{
	x = 100;
	y = 100;
	m_pParent = NULL;
	SetSize(800, 600);
	//pStart = new Button();
	//this->addChild(pStart);
	//pStart->x = 100;
	//pStart->y = 100;
	//pStart->load("ui/zhu_bg.png");
}


MainUi::~MainUi()
{

}
