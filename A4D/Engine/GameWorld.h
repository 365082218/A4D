#pragma once
class Panel;
class MainUi;
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

