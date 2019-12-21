#pragma once
#include "Panel.h"
#include "Button.h"
class MainUi :
	public Panel
{
public:
	MainUi();
	~MainUi();
	Button * pStart;
};

