#pragma once
#include "MainUi.h"
class GameWorld
{
public:
	GameWorld();
	~GameWorld();
	vector<Panel*> panels;
	MainUi * pMainUi;
	void Draw();
	void UpdateZorder();
};

