#include "stdafx.h"
#include "Panel.h"

//���,����������Ϸ����.
Panel::Panel()
{
}


Panel::~Panel()
{
}

void Panel::Load(string ui)
{

}

void Panel::draw()
{
	for (int i = 0; i < m_pChild->size(); i++)
	{
		dynamic_cast<Image2D*>((*m_pChild)[i])->draw();
	}
}