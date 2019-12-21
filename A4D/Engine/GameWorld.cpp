#include "stdafx.h"
#include "GameWorld.h"


GameWorld::GameWorld()
{
	pMainUi = new MainUi();
	panels.push_back(pMainUi);
}


GameWorld::~GameWorld()
{
}

void GameWorld::Draw()
{
	A4D::getInstance()->Graphics()->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	UpdateZorder();
	for (int i = 0; i < panels.size(); i++)
	{
		panels[i]->draw();
	}
	A4D::getInstance()->Graphics()->pSprite->End();
}

void GameWorld::UpdateZorder()
{

}