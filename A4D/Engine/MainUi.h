#pragma once
#include "Panel.h"
class Button;
class MainUi :
	public Panel
{
public:
	MainUi();
	~MainUi();
	Button * pStart;
};

