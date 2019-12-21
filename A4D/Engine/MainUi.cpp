#include "stdafx.h"
#include "MainUi.h"


MainUi::MainUi()
{
	x = 100;
	y = 100;
	m_pParent = NULL;
	SetSize(A4D::width(), (float)A4D::height());
	//pStart = new Button();
	//this->addChild(pStart);
	//pStart->x = 100;
	//pStart->y = 100;
	//pStart->load("ui/zhu_bg.png");
}


MainUi::~MainUi()
{

}
